#pragma once
#include <Gameplay/Objects.h>
#include <Gameplay/Scene.h>
#include "Player.h"
#include <system/util.hpp>
#include <vector>

namespace Gameplay {


    std::vector<sf::Vector2i> constructPath(const sf::Vector2i& a_start,
                                            const sf::Vector2i& a_end,
                                            const Scene::Scene& a_scene,
                                            int a_depth);

    void constructPath(                     const sf::Vector2i& a_start,
                                            const sf::Vector2i& a_end,
                                            const Scene::Scene& a_scene,
                                            std::vector<sf::Vector2i>& m_path,
                                            int a_depth);

    class Player: public Engine::Objects::Dynamic_Object {
    public:
        Player();
        ~Player() = default;

        void move(sf::Vector2i);

    };
}