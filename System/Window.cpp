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

    void Window::draw(const game_object::Object& obj)
    {
        RenderWindow::draw(obj.sprite);
    }
    void Window::drawScene(const Scene::Scene& scene)
    {
        { // grid draw
            sf::Vector2f size{(float)this->getSize().x, (float)this->getSize().y};
            sf::Vector2f gridOffset {scene.offset.x, scene.offset.y};
            if(gridOffset.x > scene.scale)
                gridOffset.x -= (float)((int)(gridOffset.x/scene.scale)) * scene.scale;
            if(gridOffset.y > scene.scale)
                gridOffset.y -= (float)((int)(gridOffset.y/scene.scale)) * scene.scale;

            if(gridOffset.x < scene.scale)
                gridOffset.x -= (float)((int)(gridOffset.x/scene.scale)) * scene.scale;
            if(gridOffset.y < scene.scale)
                gridOffset.y -= (float)((int)(gridOffset.y/scene.scale)) * scene.scale;

            DEB_LOG("GRID OFF: \n\t" << gridOffset.x << " - " << gridOffset.y << '\n');

            float centrX = scale*2 + gridOffset.x + size.x/2;
            float centrY = scale*2 + gridOffset.y + size.y/2;
            sf::Color color = sf::Color::Green;
            color.a = scene.scale/300.0f*255.0f;

            drawLine(sf::Vector2f(0.0f, centrY), sf::Vector2f(size.x, centrY), color);
            drawLine(sf::Vector2f(centrX, 0.0f), sf::Vector2f(centrX, size.y), color);

            for(float x = scene.scale; x <= centrX; x += scene.scale)
            {
                drawLine(sf::Vector2f(centrX - x, 0.0f), sf::Vector2f(centrX - x, size.y), color);
                drawLine(sf::Vector2f(centrX + x, 0.0f), sf::Vector2f(centrX + x, size.y), color);
            }
            for(float y = scene.scale; y <= centrY; y += scene.scale)
            {
                drawLine(sf::Vector2f(0.0f, centrY - y), sf::Vector2f(size.x, centrY - y), color);
                drawLine(sf::Vector2f(0.0f, centrY + y), sf::Vector2f(size.x, centrY + y), color);
            }
        }
    }

}
