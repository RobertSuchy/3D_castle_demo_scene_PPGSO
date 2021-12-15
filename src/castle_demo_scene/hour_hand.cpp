#include "hour_hand.h"
#include "scene.h"

#include <glm/gtx/euler_angles.hpp>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> HourHand::mesh;
std::unique_ptr<ppgso::Texture> HourHand::texture;
std::unique_ptr<ppgso::Shader> HourHand::shader;

HourHand::HourHand() {
    scale.x *= 0.5f;
    scale.y *= 3.0f;
    scale.z *= 0.4f;

    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
}

//bool HourHand::update(Scene &scene, float dt, glm::vec3 rotationOfParent) {
//    rotation = rotationOfParent;
//    rotation.x /= 60;
//    modelMatrix = glm::translate(glm::mat4{1.0f}, position)
//                  * glm::orientate4(rotation)
//                  * glm::translate(glm::mat4{1.0f},glm::vec3 {0,1.5f,0})
//                  * glm::scale(glm::mat4{1.0f}, scale);
//    return true;
//}

bool HourHand::update(Scene &scene, float dt, glm::mat4 modelMatrixOfParent) {
    modelMatrix = modelMatrixOfParent;
//    rotation = rotationOfParent;
//    rotation.x = dt / 60;
//    modelMatrix *= glm::translate(glm::mat4{1.0f}, position)
//                   * glm::orientate4(rotation)
//                   * glm::translate(glm::mat4{1.0f},glm::vec3 {0,1.75,0})
//                   * glm::scale(glm::mat4{1.0f}, scale);
    return true;
}

bool HourHand::update(Scene &scene, float dt) {}

void HourHand::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("OverallColor", glm::vec3{0.0f, 0.0f, 0.0f});

    mesh->render();
}
