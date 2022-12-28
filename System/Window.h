#pragma once
#include <SFML/Graphics.hpp>
#include "../gameplay/Object.h"
#include "../gameplay/Scene.h"
#include <iostream>

namespace Engine {
    class Window: public sf::RenderWindow {

        inline void drawLine(const sf::Vector2f& s, const sf::Vector2f& e, sf::Color frogColor = sf::Color::Green);

    public:
        float scale = 30.0;

        using RenderWindow::draw;

        Window(): RenderWindow()
        {

        }
        template<class... Args>
        Window(Args... args): RenderWindow(args...)
        {

        }

        void draw(const game_object::Object& obj, const Scene::Scene& scene);
        void drawScene(const Scene::Scene&);
        void changeScale(float);

    };
}