#pragma once
#include <vector>
#include "../System/Util.cpp"
#include "Object.h"

namespace Engine {
    class Window;
}

namespace Scene {
    class Scene {
        /*
         * Сцена - область из клеток.
         * Нуль-точка - Середина.(нахуя)
         * */


        std::vector<game_object::Object> objects;
        float scale = 30.0;

        friend Engine::Window;
    public:
        sf::Vector2f offset{0, 0};


        enum type_t {
            INFINITY_GENERATION,
            FIXED,
            DYNAMIC_SCENE
        } type;

        Scene(type_t);

        template<typename V, typename V::Object T>
        void insert(const V&);

        template<class T>
        T& create();

        void changeScale(float);
        void setScale(float);
    };
};