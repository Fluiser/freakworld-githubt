#pragma once
#include <iostream>
#include "Scene.h"

namespace Scene {
    Scene::Scene::Scene(type_t t):
    type(t)
    {

    }

    template<typename V, typename V::Object T>
    void Scene::insert(const V& obj)
    {
        ((V)this->objects).emplace_back();
        auto& o = objects.back();
        o.gpos = obj.gpos;
        o.texture = obj.texture;

        if(o.texture)
            o.sprite.setTexture(*o.texture);
    }

    game_object::Object get(sf::Vector2i);

    template<class T>
    T& Scene::create()
    {
        ((std::vector<T>)this->objects).emplace_back();
        return (T)this->objects.back();
    }

    void Scene::setScale(float s)
    {
        if(s > 254)
        {
            scale = 254.0f;
            return;
        }
        if(s < 0.1)
        {
            scale = 0.1f;
            return;
        }
        offset.x = offset.x/scale*s;
        offset.y = offset.y/scale*s;
        scale = s;
    }

    game_object::Object* Scene::get(sf::Vector2i v)
    {
        for (auto& obj : this->objects)
        {
            if (obj.gpos.x == v.x && obj.gpos.y == v.y)
                return &obj;
        }
        return nullptr;
    }

    int Scene::separateFloat(float n)
    {
        return n >= 0 ?
            (float)((int)n) < n ?
                (int)(n + 1) : (int)n
            :
            (float)((int)n) > n ?
                (int)(n - 1) : (int)n;
    }

    sf::Vector2f Scene::getPosition(sf::Vector2i p)
    {

        return sf::Vector2f(
            (((float)p.x) * (scale)),
            (((float)-p.y) * (scale))
        );
    }

    Scene::area_t Scene::getVisibleArea(sf::Vector2u visibleArea)
    {
        return area_t{
            sf::Vector2i(   Scene::separateFloat(((float)visibleArea.x/2)/scale ),
                                Scene::separateFloat(((float)visibleArea.y / 2) / scale)
                        ),
            sf::Vector2i(   Scene::separateFloat((float)(offset.x + visibleArea.x) / scale),
                                Scene::separateFloat((float)(offset.y + visibleArea.y) / scale )
                        )
        };
    }

    const float& Scene::getScale() const noexcept
    {
        return this->scale;
    }

    void Scene::changeScale(float s)
    {
        float nscale = scale + s;
        this->setScale(nscale);
    }
};
