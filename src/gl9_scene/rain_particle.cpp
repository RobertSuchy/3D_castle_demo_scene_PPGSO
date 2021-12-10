#include <glm/gtc/random.hpp>
#include "rain_particle.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

// Static resources
std::unique_ptr<ppgso::Mesh> RainParticle::mesh;
std::unique_ptr<ppgso::Texture> RainParticle::texture;
std::unique_ptr<ppgso::Shader> RainParticle::shader;

RainParticle::RainParticle() {
    // Set random scale speed and rotation
    scale *= glm::linearRand(0.25f, 0.5f);
    speed = {glm::linearRand(-2.0f, 2.0f), glm::linearRand(-5.0f, -10.0f), 0.0f};
    rotation = glm::ballRand(ppgso::PI);
    rotMomentum = glm::ballRand(ppgso::PI);

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
//    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("fire_particle_texture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool RainParticle::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;

    // Animate position according to time
//    position -= speed * dt;
//    position.x += std::sin(age * 2) / 100;
    position.y -= 0.5f;
//    position.z += std::sin(age * 2) / 100;
    scale *= 0.998;
    if (position.y < 1) {
        return false;
    }

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void RainParticle::render(Scene &scene) {
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



