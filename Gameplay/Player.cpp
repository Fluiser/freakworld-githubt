#include "Player.h"
#include <stdint.h>
#include <System/Range.hpp>
#define DEBUG
#include <System/Util.hpp>

namespace {

}

namespace Gameplay {
    
    std::vector<sf::Vector2i> constructPath(const sf::Vector2i& start,
                                            const sf::Vector2i& end,
                                            Scene::Scene& scene,
                                            int max_depth)
    {
        std::vector<sf::Vector2i> m_vector;
        constructPath(start, end, scene, m_vector, max_depth);
        return m_vector;
    }

    void constructPath(                     const sf::Vector2i& start,
                                            const sf::Vector2i& end,
                                            Scene::Scene& scene,
                                            std::vector<sf::Vector2i>& vec_path,
                                            int max_depth)
    {
        int depth = max_depth;
        auto size = end-start;

        if( (abs(end.x-start.x) + abs(end.y - start.y) + 1) > depth) return;

        // use path[y][x];
        std::vector<std::vector<uint8_t>> path(depth*2);
        for(const auto& y: Math::Range<int>(   (start.y - depth),
                                               (start.y + depth),
                                                1)) // стоить формулу пути, т.к. не всё отталкивается от точек конца
        {
            path.emplace_back(std::vector<uint8_t>(depth*2));
            auto& _p = path.back();
            
            for(const auto& x: Math::Range<int>(
                 start.x - depth,
                 start.x + depth,
                 1))
            {
                _p.emplace_back(scene.get(sf::Vector2i(x, y)) ? 0 : 0xff);
            }
        }
        // Матрица типа [y][x] с весами.
        /**
         * Сначала стоит пройтись по квадратам, мол, есть ли вообще клетки, по которым можно пройтись.
         * А потом да.
        */
        

        // C++17 всё ещё сосёт.
        // Перемещать адекватно значения мы не умеем.
    }



    Player::Player(): Engine::Objects::Dynamic_Object() {}

    
}