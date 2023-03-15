#pragma once
#include <Gameplay/Objects.h>
#include <Gameplay/Scene.h>
#include "Player.h"
#include <vector>

namespace Gameplay {


    std::vector<sf::Vector2i> constructPath(const sf::Vector2i& start,
                                            const sf::Vector2i& end,
                                            Scene::Scene& scene,
                                            int max_depth);

    void constructPath(                     const sf::Vector2i& start, // Начальная позиция 
                                            const sf::Vector2i& end, // Конечная позиция
                                            Scene::Scene& scene, // Сцена
                                            std::vector<sf::Vector2i>& path, // построенный путь. перенимание данных отдаётся компилятору, которому мы не доверяем.
                                            int max_depth); // Макс. грубина.

    class Player: public Engine::Objects::Dynamic_Object {
    public:
        Player();
        ~Player() = default;

        void move(sf::Vector2i);

    };
}