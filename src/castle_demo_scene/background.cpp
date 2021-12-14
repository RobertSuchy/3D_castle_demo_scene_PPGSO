#include "background.h"
#include "scene.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Background::mesh;
std::unique_ptr<ppgso::Texture> Background::texture;
std::unique_ptr<ppgso::Shader> Background::shader;

Background::Background() {
    scale *= -25000.0f;

    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool Background::update(Scene &scene, float dt) {

    generateModelMatrix();
    return true;
}

void Background::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("OverallColor", glm::vec3{0.68f, 0.85f, 0.90f});

    mesh->render();
}
