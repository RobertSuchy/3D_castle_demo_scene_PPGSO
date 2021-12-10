#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>

#include "generator.h"
#include "fire_particle.h"
#include "rain_particle.h"

bool Generator::update(Scene &scene, float dt) {
    // Accumulate time
    time += dt;

    // Add object to scene when time reaches certain level
    if (time < 59.0f) {
        auto obj = std::make_unique<FireParticle>();
//        obj->position = position;
        obj->position.x += glm::linearRand(-45.0f, -55.0f);
        obj->position.y += glm::linearRand(5.0f, 15.0f);
        obj->position.z += glm::linearRand(-70.0f, -80.0f);
        scene.objects.push_back(move(obj));
    }

    for (int i = 0; i < 5; i++) {
        auto obj = std::make_unique<RainParticle>();
//        obj->position = position;
        obj->position.x += glm::linearRand(-100.0f, 100.0f);
        obj->position.y += glm::linearRand(100.0f, 150.0f);
        obj->position.z += glm::linearRand(-100.0f, 100.0f);
        scene.objects.push_back(move(obj));
    }

//    if (time > 57.0f) {

//    }

    return true;
}

void Generator::render(Scene &scene) {
    // Generator will not be rendered
}
