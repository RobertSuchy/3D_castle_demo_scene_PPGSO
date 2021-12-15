#include "scene.h"

void Scene::update(float time) {
    camera->update(time);

    auto i = std::begin(objects);
    while (i != std::end(objects)) {
        auto obj = i->get();
        if (!obj->update(*this, time))
            i = objects.erase(i);
        else
            ++i;
    }
}

void Scene::render() {
    for (auto &obj: objects)
        obj->render(*this);
}