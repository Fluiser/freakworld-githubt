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
        float scale = 100.0;

        friend Engine::Window;
    
    protected:
        inline int separateFloat(float n);
    public:
        sf::Vector2i offset{0, 0};

        struct area_t {
            sf::Vector2i start;
            sf::Vector2i end;
        };


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

        game_object::Object* get(sf::Vector2i);

        area_t getVisibleArea(sf::Vector2u);
        sf::Vector2f getPosition(sf::Vector2i);

        void changeScale(float);
        void setScale(float);

        const float& getScale() const noexcept;
    };
};