#include <glm/gtc/random.hpp>
#include "asteroid.h"
#include "ground.h"
#include "explosion.h"
#include "castle.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Asteroid::mesh;
std::unique_ptr<ppgso::Texture> Asteroid::texture;
std::unique_ptr<ppgso::Shader> Asteroid::shader;

Asteroid::Asteroid() {
    scale *= 2.0f;
    speed = {glm::linearRand(-2.0f, 2.0f), glm::linearRand(-500.0f, -1000.0f), 0.0f};
    rotation = glm::ballRand(ppgso::PI);
    rotMomentum = glm::ballRand(ppgso::PI);

    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("asteroid.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("asteroid.obj");
}

bool Asteroid::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;

    // Animate position according to time
    position += speed * (dt / 2);

    // Rotate the object
    rotation += rotMomentum * (dt / 5);

    // Delete when alive longer than 10s or out of visibility
//    if (age > 10.0f || position.y < -10) return false;

    // Collide with scene
//    for (auto &obj: scene.objects) {
//        // Ignore self in scene
//        if (obj.get() == this) continue;
//
//        // We only need to collide with asteroids and projectiles, ignore other objects
////        auto asteroid = dynamic_cast<Asteroid *>(obj.get()); // dynamic_pointer_cast<Asteroid>(obj);
//        auto ground = dynamic_cast<Ground *>(obj.get()); //dynamic_pointer_cast<Projectile>(obj);
////        if (!asteroid && !ground) continue;
//        if (!ground) continue;
//
////        // When colliding with other asteroids make sure the object is older than .5s
////        // This prevents excessive collisions when asteroids explode.
//
//        // Compare distance to approximate size of the asteroid estimated from scale.
//        if (distance(position, obj->position) < (obj->scale.y + scale.y) * 1.0f) {
////            int pieces = 3;
////
////            // Too small to split into pieces
////            if (scale.y < 0.5) pieces = 0;
//
//            // The projectile will be destroyed
////            if (projectile) projectile->destroy();
//
//            // Generate smaller asteroids
////            explode(scene, (obj->position + position) / 2.0f, (obj->scale + scale) / 2.0f);
//////            if (asteroid && age < 5.0f) {
//////                return false;
//////            }
////
////            reproduce(scene);
//
//            // Destroy self
//            return false;
//        }
//    }

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Asteroid::reproduce(Scene &scene) {
    // Generate smaller asteroids
    for (int i = 0; i < 5; i++) {
        auto obj = std::make_unique<Asteroid>();
        obj->position = position;
        obj->position.y += 1000.0f;
        obj->position.x += glm::linearRand(-1000.0f, 1000.0f);
        obj->position.z += glm::linearRand(-1000.0f, 1000.0f);
//        obj->scale = scale / 5.0f;
        scene.objects.push_back(move(obj));
//        auto asteroid = std::make_unique<Asteroid>();
//        asteroid->speed = speed + glm::vec3(glm::linearRand(-3.0f, 3.0f), glm::linearRand(0.0f, -5.0f), 0.0f);;
//        asteroid->position = position;
//        asteroid->rotMomentum = rotMomentum;
//        float factor = (float) 3 / 2.0f;
//        asteroid->scale = scale / factor;
//        scene.objects.push_back(move(asteroid));
    }
}


void Asteroid::explode(Scene &scene, glm::vec3 explosionPosition, glm::vec3 explosionScale) {
    // Generate explosion
    auto explosion = std::make_unique<Explosion>();
    explosion->position = explosionPosition;
    explosion->scale = explosionScale;
    explosion->speed = speed / 2.0f;
    scene.objects.push_back(move(explosion));
}

void Asteroid::render(Scene &scene) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}

//void Asteroid::onClick(Scene &scene) {
//    std::cout << "Asteroid clicked!" << std::endl;
//    explode(scene, position, {10.0f, 10.0f, 10.0f}, 0);
//    age = 10000;
//}

