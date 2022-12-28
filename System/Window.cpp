#include "Window.h"
#include "./Util.cpp"
#pragma once

namespace Engine {
    inline void Window::drawLine(const sf::Vector2f& s, const sf::Vector2f& e, sf::Color frogColor)
    {
        // line line(s, e, w, frogColor);
        // line.draw(*this);
        sf::VertexArray lines(sf::Lines, 2);
        lines[0].position = s;
        lines[1].position = e;
        lines[0].color = lines[1].color = frogColor;
        RenderWindow::draw(lines);
    }

    void Window::draw(const game_object::Object& obj, const Scene::Scene& scene)
    {
        obj.render(*this, scene);
    }


    /*
     * Переписать сия чудо.
     *
     * Рендер избыточен и некорректен с высоким числом оффсета.
     * И херня в принципе.
     * 
     * Рендер туфта. Либо используем double и плачем, либо плачем и рыдаем, и переделываем.
     * Я - я и я. Вот это мы!
     * */
    void Window::drawScene(const Scene::Scene& scene)
    {
        { // grid draw
            sf::Vector2i size{(int)this->getSize().x, (int)this->getSize().y};
            sf::Vector2i gridOffset {scene.offset.x, scene.offset.y};

            // Int, ибо мы теряем теряемое без познаний о потерянном.
            if(gridOffset.x > scene.scale)
                gridOffset.x -= (int)((float)((int)(gridOffset.x/scene.scale)) * scene.scale);
            if(gridOffset.y > scene.scale)
                gridOffset.y -= (int)((float)((int)(gridOffset.y/scene.scale)) * scene.scale);

            if(gridOffset.x < scene.scale)
                gridOffset.x -= (int)((float)((int)(gridOffset.x/scene.scale)) * scene.scale);
            if(gridOffset.y < scene.scale)
                gridOffset.y -= (int)((float)((int)(gridOffset.y/scene.scale)) * scene.scale);



            float centrX = (float)(size.x/2 - gridOffset.x);
            float centrY = (float)(size.y/2 + gridOffset.y);

            sf::Color color = sf::Color::Green;
            color.a = (unsigned char)(scene.scale/300.0f*255.0f);

            drawLine(sf::Vector2f(0.0f, centrY), sf::Vector2f((float)size.x, (float)centrY), color);
            drawLine(sf::Vector2f(centrX, 0.0f), sf::Vector2f((float)centrX, (float)size.y), color);

            const float __endpoint_render__endx = centrX + scene.scale*2;
            const float __endpoint_render__endy = centrY + scene.scale*2;

            for(float x = scene.scale; x <= __endpoint_render__endx; x += scene.scale)
            {
                drawLine(sf::Vector2f((float)(centrX - x), 0.0f), sf::Vector2f((float)(centrX - x), (float)size.y), color);
                drawLine(sf::Vector2f((float)(centrX + x), 0.0f), sf::Vector2f((float)(centrX + x), (float)size.y), color);
            }
            for(float y = scene.scale; y <= __endpoint_render__endy; y += scene.scale)
            {
                drawLine(sf::Vector2f(0.0f, (float)(centrY - y)), sf::Vector2f((float)size.x, (float)(centrY - y)), color);
                drawLine(sf::Vector2f(0.0f, (float)(centrY + y)), sf::Vector2f((float)size.x, (float)(centrY + y)), color);
            }
        }

        for (auto& ptr : scene.objects)
        {
            ptr->normalize(*this, scene);
            ptr->render(*this, scene);
        }
    }

}
