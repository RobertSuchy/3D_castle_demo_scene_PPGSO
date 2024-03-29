#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>

#include "generator.h"
#include "fire_particle.h"
#include "spear.h"

bool Generator::update(Scene &scene, float dt) {
    time += dt;

    auto obj = std::make_unique<FireParticle>();
    obj->position.x += glm::linearRand(-5.0f, 5.0f);
    obj->position.y += glm::linearRand(5.0f, 15.0f);
    obj->position.z += glm::linearRand(-70.0f, -80.0f);
    scene.objects.push_back(move(obj));

    // vygeneruje sa spear do veže
    if (time >= 105.0f && spearCount == 0) {
        auto spear = std::make_unique<Spear>();
        spear->position.x = -55.0f;
        scene.objects.push_back(move(spear));
        spearCount++;
    }

    // vygeneruje sa spear do kamery
    if (time >= 111.0f && spearCount == 1) {
        auto spear = std::make_unique<Spear>();
        spear->position.x = -100.0f;
        scene.objects.push_back(move(spear));
        spearCount++;
    }

    return true;
}

void Generator::render(Scene &scene) {}
