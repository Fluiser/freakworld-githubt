#include "Player.h"
#include <utility>
#define DEBUG
#include <system/Util.hpp>

namespace {
}

namespace Gameplay {
    std::vector<sf::Vector2i> constructPath(const sf::Vector2i& a_start,
                                            const sf::Vector2i& a_end,
                                            const Scene::Scene& a_scene,
                                            int a_depth)
    {
        std::vector<sf::Vector2i> m_vector;
        constructPath(a_start, a_end, a_scene, m_vector, a_depth);
        return m_vector;
    }
    void constructPath(const sf::Vector2i& a_start,
                                            const sf::Vector2i& a_end,
                                            const Scene::Scene& a_scene,
                                            std::vector<sf::Vector2i>& m_path,
                                            int a_depth)
    {
        m_path.resize(a_depth);
        auto m_start = a_start;
        auto m_depth = a_depth;
        while( m_depth > 0 )
        {
            if(m_start.x != a_end.x)
            {
                /*
                    c = (a_end.x - m_start.x)
                    c = { 0, если c = 0
                        { 1, если с > 0
                        { -1, если c < 0
                */
                m_start.x += (a_end.x - m_start.x) > 0 ? 1 : (a_end.x - m_start.x) < 0 ? -1 : 0;
            } else if(m_start.y != a_end.y)
            {
                m_start.y += (a_end.y - m_start.y) > 0 ? 1 : (a_end.y - m_start.y) < 0 ? -1 : 0;
            } else {
                break;
            }
            m_path.emplace_back(m_start);
            --m_depth;
        }

        // C++17 всё ещё сосёт.
        // Перемещать адекватно значения мы не умеем.
    }



    Player::Player(): Engine::Objects::Dynamic_Object() {}

    
}