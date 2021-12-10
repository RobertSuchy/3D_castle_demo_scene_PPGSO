#include "background.h"
#include "scene.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

// shared resources
std::unique_ptr<ppgso::Mesh> Background::mesh;
std::unique_ptr<ppgso::Texture> Background::texture;
std::unique_ptr<ppgso::Shader> Background::shader;

Background::Background() {
    // Scale the default model
    scale *= -11000.0f;

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
//    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("sky.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool Background::update(Scene &scene, float dt) {

    generateModelMatrix();
    return true;
}

void Background::render(Scene &scene) {
    shader->use();

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
//    shader->setUniform("OverallColor", glm::vec3{0.53f, 0.81f, 0.92f});
    shader->setUniform("OverallColor", glm::vec3{0.68f, 0.85f, 0.90f});

    mesh->render();
}
