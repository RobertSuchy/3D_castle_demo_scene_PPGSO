#include "bird.h"
#include "scene.h"

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>

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
    age += dt;
    Keyframe currentKeyframe = keyframes[currentKeyframeIndex];
    if (currentKeyframe.age == 0) {
        return false;
    }

    glm::mat4 currentModelMatrix = glm::translate(glm::mat4{1.0f}, currentKeyframe.pos)
                             * glm::orientate4(currentKeyframe.rot)
                             * glm::scale(glm::mat4{1.0f}, currentKeyframe.scl);

    Keyframe nextKeyframe = keyframes[currentKeyframeIndex + 1];
    glm::mat4 nextModelMatrix = glm::translate(glm::mat4{1.0f}, nextKeyframe.pos)
                             * glm::orientate4(nextKeyframe.rot)
                             * glm::scale(glm::mat4{1.0f}, nextKeyframe.scl);

    auto prevAge = 0.0f;
    if (currentKeyframeIndex > 0) {
        prevAge = keyframes[currentKeyframeIndex - 1].age;
    }
    modelMatrix = glm::mix(currentModelMatrix, nextModelMatrix, (age - prevAge) / (currentKeyframe.age - prevAge));

    if (age > currentKeyframe.age) {
        currentKeyframeIndex++;
    }
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
