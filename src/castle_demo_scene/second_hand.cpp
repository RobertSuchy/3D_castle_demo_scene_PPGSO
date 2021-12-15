#include "second_hand.h"
#include "scene.h"

#include <glm/gtx/euler_angles.hpp>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> SecondHand::mesh;
std::unique_ptr<ppgso::Texture> SecondHand::texture;
std::unique_ptr<ppgso::Shader> SecondHand::shader;

SecondHand::SecondHand() {
    scale.x *= 0.5f;
    scale.y *= 3.5f;
    scale.z *= 0.15f;

    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");

    // pridanie minútovej ručičky ako child
    child = std::make_unique<MinuteHand>();
    child->position.x = -97.5f;
    child->position.y = 27.7f;
    child->position.z = -39.75f;
}

bool SecondHand::update(Scene &scene, float dt) {
    age += dt;
    rotation.x = -age * 6;
    modelMatrix = glm::translate(glm::mat4{1.0f}, position)
                  * glm::orientate4(rotation)
                  * glm::translate(glm::mat4{1.0f},glm::vec3 {0,1.75f,0})
                  * glm::scale(glm::mat4{1.0f}, scale);

    child->update(scene, dt, rotation);
    child->render(scene);

    return true;
}

void SecondHand::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("OverallColor", glm::vec3{0.5f, 0.5f, 0.5f});

    mesh->render();
}
