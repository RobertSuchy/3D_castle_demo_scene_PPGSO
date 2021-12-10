#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>

#include "generator.h"
#include "fire_particle.h"

bool Generator::update(Scene &scene, float dt) {
  // Accumulate time
  time += dt;

  // Add object to scene when time reaches certain level
//  if (time > .0001) {
    auto obj = std::make_unique<FireParticle>();
    obj->position = position;
//    obj->position.x += glm::linearRand(-20.0f, 20.0f);
    obj->position.x += glm::linearRand(-45.0f, -55.0f);
    obj->position.z += glm::linearRand(-70.0f, -80.0f);
    scene.objects.push_back(move(obj));
    time = 0;
//  }

  return true;
}

void Generator::render(Scene &scene) {
  // Generator will not be rendered
}
