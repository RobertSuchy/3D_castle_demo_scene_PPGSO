#include "minute_hand.h"
#include "scene.h"
#include <glm/gtx/string_cast.hpp>

#include <glm/gtx/euler_angles.hpp>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> MinuteHand::mesh;
std::unique_ptr<ppgso::Texture> MinuteHand::texture;
std::unique_ptr<ppgso::Shader> MinuteHand::shader;

MinuteHand::MinuteHand() {
    scale.x *= 0.5f;
    scale.y *= 3.5f;
    scale.z *= 0.25f;

    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");

    // pridanie hodinovej ručičky ako child
    child = std::make_unique<HourHand>();
    child->position.x = -97.5f;
    child->position.y = 27.7f;
    child->position.z = -39.75f;
}

bool MinuteHand::update(Scene &scene, float dt, glm::vec3 rotationOfParent) {
    rotation = rotationOfParent;
    rotation.x /= 60;
    modelMatrix = glm::translate(glm::mat4{1.0f}, position)
                  * glm::orientate4(rotation)
                  * glm::translate(glm::mat4{1.0f},glm::vec3 {0,1.75,0})
                  * glm::scale(glm::mat4{1.0f}, scale);

    child->update(scene, dt, rotation);
    child->render(scene);

    return true;
}

bool MinuteHand::update(Scene &scene, float dt) {}

void MinuteHand::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("OverallColor", glm::vec3{0.0f, 0.0f, 0.0f});

    mesh->render();
}
