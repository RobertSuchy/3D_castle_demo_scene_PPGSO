#include <glm/gtc/random.hpp>
#include "fire_particle.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> FireParticle::mesh;
std::unique_ptr<ppgso::Texture> FireParticle::texture;
std::unique_ptr<ppgso::Shader> FireParticle::shader;

FireParticle::FireParticle() {
    // nastavenie náhodného škálovania a rotácie
    scale *= glm::linearRand(0.5f, 1.0f);
    rotation = glm::ballRand(ppgso::PI);

    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool FireParticle::update(Scene &scene, float dt) {
    age += dt;

    position += gravity * dt;
    position += wind/scale;

    scale *= 0.998;
    if (position.y > 75) {
        return false;
    }

    generateModelMatrix();

    return true;
}

void FireParticle::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("OverallColor", glm::vec3{0.25, 0.25, 0.25});

    mesh->render();
}
