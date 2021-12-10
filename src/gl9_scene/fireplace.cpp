#include "fireplace.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

// shared resources
std::unique_ptr<ppgso::Mesh> Fireplace::mesh;
std::unique_ptr<ppgso::Texture> Fireplace::texture;
std::unique_ptr<ppgso::Shader> Fireplace::shader;

Fireplace::Fireplace() {
    // Scale the default model
    scale *= 0.5f;

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("fireplace_texture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("fireplace.obj");
}

bool Fireplace::update(Scene &scene, float dt) {

    generateModelMatrix();
    return true;
}

void Fireplace::render(Scene &scene) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}


