#include "Player.h"
#include <stdint.h>
#include <System/Range.hpp>
#define DEBUG
#include <Gameplay/Objects/Static_Object.h>
#include <System/Util.hpp>

namespace {
    bool _objectsCanClip(const std::list<Engine::Objects::Static_Object> vec)
    {
        for(const auto& obj: vec)
        {
            if(obj.clip) return true;
        }
        return false;
    }

    int _WayCost(const std::list<Engine::Objects::Static_Object> obj)
    {
        return 1; // На будущее.
    }

    struct Node {
        Node* parent;
        int weight;
        sf::Vector2i pos;
    };
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
        auto p = start;
        int sy = start.y < end.y ? 1 : -1;
        int sx = start.x < end.x ? 1 : -1;

        while((p.x != end.x || p.y != end.y) && max_depth > 0)
        {
            if(p.x != end.x) {
                p.x += sx;
                --max_depth;
                const auto* list = scene.get<Engine::Objects::Static_Object>(p);
                if(list != nullptr && _objectsCanClip(*list)) return;
                vec_path.emplace_back(p);
            }
            if(p.y != end.y && max_depth > 0) {
                p.y += sy;
                --max_depth;
                const auto* list = scene.get<Engine::Objects::Static_Object>(p);
                if(list != nullptr && _objectsCanClip(*list)) return;
                vec_path.emplace_back(p);
            }
        }


        // C++17 всё ещё сосёт.
        // Перемещать адекватно значения мы не умеем.
    }



    Player::Player(): Engine::Objects::Dynamic_Object() {}

    
}
