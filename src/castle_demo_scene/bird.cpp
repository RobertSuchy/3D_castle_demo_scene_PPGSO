#include "bird.h"
#include "scene.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Bird::mesh;
std::unique_ptr<ppgso::Shader> Bird::shader;

Bird::Bird() {
    scale *= 35.0f;

    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("eagle.obj");
}

bool Bird::update(Scene &scene, float dt) {

    generateModelMatrix();
    return true;
}

void Bird::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("OverallColor", glm::vec3{0.28f, 0.24f, 0.2f});

    mesh->render();
}
