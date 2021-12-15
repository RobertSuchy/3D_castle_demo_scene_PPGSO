#include "fireplace_shadow.h"
#include "scene.h"

#include <glm/gtx/euler_angles.hpp>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>


std::unique_ptr<ppgso::Mesh> FireplaceShadow::mesh;
std::unique_ptr<ppgso::Shader> FireplaceShadow::shader;

FireplaceShadow::FireplaceShadow() {
    scale.x *= 0.2f;
    scale.y *= 0.2f;
    scale.z *= 0.001f;

    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("fireplace.obj");
}

bool FireplaceShadow::update(Scene &scene, float dt) {
    modelMatrix = glm::translate(glm::mat4(1.0f), position)
                  * glm::orientate4(glm::vec3 {-M_PI / 2.0f, 0, 0})
                  * glm::translate(glm::mat4(1.0f), {0.0f, 0.0f, 0.0f})
                  * glm::scale(glm::mat4(1.0f), {1, 1.25f, 1})
                  * glm::translate(glm::mat4(1.0f), {0.0f, 0.5f * 1.25f, 0})
                  * glm::scale(glm::mat4(1.0f), scale);
    return true;
}

void FireplaceShadow::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("OverallColor", glm::vec3{0, 0, 0});
    mesh->render();
}
