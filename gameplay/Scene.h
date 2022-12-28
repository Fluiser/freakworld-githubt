#pragma once
#include <vector>
#include <memory>
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


        std::vector<std::unique_ptr<game_object::Object>> objects;
        float scale = 100.0;

        friend Engine::Window;
    
    protected:
        inline int separateFloat(float n) const;
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
        T& create()
        {
            this->objects.emplace_back(std::make_unique<T>());
            return *((T*)this->objects.back().get());
        }

        game_object::Object* get(sf::Vector2i);

        area_t getVisibleArea(sf::Vector2u) const;
        sf::Vector2f getPositionf(sf::Vector2i) const;
        sf::Vector2i getPositioni(sf::Vector2i p) const;

        void changeScale(float);
        void setScale(float);

        const float& getScale() const noexcept;
    };
};