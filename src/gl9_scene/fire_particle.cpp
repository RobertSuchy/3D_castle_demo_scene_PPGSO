#include <glm/gtc/random.hpp>
#include "fire_particle.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

// Static resources
std::unique_ptr<ppgso::Mesh> FireParticle::mesh;
std::unique_ptr<ppgso::Texture> FireParticle::texture;
std::unique_ptr<ppgso::Shader> FireParticle::shader;

FireParticle::FireParticle() {
    // Set random scale speed and rotation
    scale *= glm::linearRand(0.5f, 1.0f);
    speed = glm::linearRand(0.8f, 1.2f);
    rotation = glm::ballRand(ppgso::PI);
    rotMomentum = glm::ballRand(ppgso::PI);

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
//    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("fire_particle_texture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool FireParticle::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;

    // Animate position according to time
//    position -= speed * dt;
    position.x += std::sin(age * 2) / 100;
    position.y += speed * 0.075f;
    position.z += std::sin(age * 2) / 100;
    scale *= 0.998;
    if (position.y > 75) {
        return false;
    }

    // Rotate the object
//    rotation += rotMomentum * dt;

    // Delete when alive longer than 10s or out of visibility
//    if (age > 10.0f || position.y < -10) return false;

    // Collide with scene
//    for (auto &obj : scene.objects) {
//        // Ignore self in scene
//        if (obj.get() == this) continue;
//
//        // We only need to collide with asteroids and projectiles, ignore other objects
//        auto fireParticle = dynamic_cast<FireParticle*>(obj.get()); // dynamic_pointer_cast<Asteroid>(obj);
////        auto projectile = dynamic_cast<Projectile*>(obj.get()); //dynamic_pointer_cast<Projectile>(obj);
////        if (!asteroid && !projectile) continue;
//
//        // When colliding with other asteroids make sure the object is older than .5s
//        // This prevents excessive collisions when asteroids explode.
////        if (asteroid && age < 0.5f) continue;
//
//        // Compare distance to approximate size of the asteroid estimated from scale.
//        if (distance(position, obj->position) < (obj->scale.y + scale.y) * 0.7f) {
//            int pieces = 3;
//
//            // Too small to split into pieces
//            if (scale.y < 0.5) pieces = 0;
//
//            // The projectile will be destroyed
////            if (projectile) projectile->destroy();
//
//            // Generate smaller asteroids
////            explode(scene, (obj->position + position) / 2.0f, (obj->scale + scale) / 2.0f, pieces);
//
//            // Destroy self
//            return false;
//        }
//    }

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

//void FireParticle::explode(Scene &scene, glm::vec3 explosionPosition, glm::vec3 explosionScale, int pieces) {
//    // Generate explosion
//    auto explosion = std::make_unique<Explosion>();
//    explosion->position = explosionPosition;
//    explosion->scale = explosionScale;
//    explosion->speed = speed / 2.0f;
//    scene.objects.push_back(move(explosion));
//
//    // Generate smaller asteroids
//    for (int i = 0; i < pieces; i++) {
//        auto asteroid = std::make_unique<Asteroid>();
//        asteroid->speed = speed + glm::vec3(glm::linearRand(-3.0f, 3.0f), glm::linearRand(0.0f, -5.0f), 0.0f);;
//        asteroid->position = position;
//        asteroid->rotMomentum = rotMomentum;
//        float factor = (float) pieces / 2.0f;
//        asteroid->scale = scale / factor;
//        scene.objects.push_back(move(asteroid));
//    }
//}

void FireParticle::render(Scene &scene) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
//    shader->setUniform("Texture", *texture);
    shader->setUniform("OverallColor", glm::vec3{0.25, 0.25, 0.25});

    mesh->render();
}

//void FireParticle::onClick(Scene &scene) {
//    std::cout << "Asteroid clicked!" << std::endl;
//    explode(scene, position, {10.0f, 10.0f, 10.0f}, 0 );
//    age = 10000;
//}

