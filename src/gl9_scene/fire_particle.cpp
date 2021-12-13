#include <glm/gtc/random.hpp>
#include "fire_particle.h"

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

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
//    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("fire_particle_texture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool FireParticle::update(Scene &scene, float dt) {
    age += dt;

//    position.x += std::sin(age * 2) / 100;
//    position.z += std::sin(age * 2) / 100;

    position.y += speed * 0.075f;
    position += scale * wind * (age/4);

    scale *= 0.998;
    if (position.y > 75) {
        return false;
    }

    generateModelMatrix();

    return true;
}

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

