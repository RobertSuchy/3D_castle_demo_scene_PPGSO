#include "clock.h"
#include "scene.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

#include <shaders/convolution_vert_glsl.h>
#include <shaders/convolution_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Clock::mesh;
std::unique_ptr<ppgso::Texture> Clock::texture;
std::unique_ptr<ppgso::Shader> Clock::shader;

Clock::Clock() {
    scale.x *=  0.5f;
    scale.y *=  9.0f;
    scale.z *=  9.0f;

//    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!shader) shader = std::make_unique<ppgso::Shader>(convolution_vert_glsl, convolution_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");

    // pridanie sekundovej ručičky
    secondHand = std::make_unique<SecondHand>();
    secondHand->position.x = -97.5f;
    secondHand->position.y = 27.7f;
    secondHand->position.z = -39.75f;
}

bool Clock::update(Scene &scene, float dt) {
    secondHand->update(scene, dt);
    secondHand->render(scene);

    generateModelMatrix();
    return true;
}

void Clock::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
//    shader->setUniform("OverallColor", glm::vec3{0.75f, 0.75f, 0.75f});

    mesh->render();
}
