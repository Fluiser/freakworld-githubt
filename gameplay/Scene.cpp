#pragma once
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
            scale = 254;
            return;
        }
        if(s < 0.1)
        {
            scale = 0.1;
            return;
        }
        scale = s;
    }

    void Scene::changeScale(float s)
    {
        float nscale = scale + s;
        this->setScale(nscale);
    }
};