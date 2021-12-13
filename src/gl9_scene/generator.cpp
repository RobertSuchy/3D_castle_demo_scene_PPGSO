#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>

#include "generator.h"
#include "fire_particle.h"
#include "asteroid.h"

bool Generator::update(Scene &scene, float dt) {
    // Accumulate time
    time += dt;

    auto obj = std::make_unique<FireParticle>();
    obj->position.x += glm::linearRand(-5.0f, 5.0f);
    obj->position.y += glm::linearRand(5.0f, 15.0f);
    obj->position.z += glm::linearRand(-70.0f, -80.0f);
    scene.objects.push_back(move(obj));

//    if (time > .3) {
//        auto obj = std::make_unique<Asteroid>();
//        obj->position = position;
//        obj->position.x += glm::linearRand(-20.0f, 20.0f);
//        scene.objects.push_back(move(obj));
//        time = 0;
//    }

    return true;
}

void Generator::render(Scene &scene) {
    // Generator will not be rendered
}
