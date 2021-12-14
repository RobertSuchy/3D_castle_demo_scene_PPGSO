#include <glm/gtc/random.hpp>
#include "wall_particle.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> WallParticle::mesh;
std::unique_ptr<ppgso::Texture> WallParticle::texture;
std::unique_ptr<ppgso::Shader> WallParticle::shader;

WallParticle::WallParticle() {
    scale *= glm::linearRand(2.0f, 3.0f);
    force = {glm::linearRand(-0.5f, 0.5f), glm::linearRand(-0.1f, 0.1f), glm::linearRand(0.15f, 0.25f)};
    rotation = glm::ballRand(ppgso::PI);

    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool WallParticle::update(Scene &scene, float dt) {
    age += dt;

    position += gravity * scale;
    position += force * scale;

    scale *= 0.98;

    if (scale.x < 0.1) {
        return false;
    }

    generateModelMatrix();

    return true;
}

void WallParticle::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);

    shader->setUniform("OverallColor", glm::vec3{0.53, 0.44, 0.31});

    mesh->render();
}

