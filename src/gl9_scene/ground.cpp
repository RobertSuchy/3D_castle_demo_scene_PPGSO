#include "scene.h"
#include "ground.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

// shared resources
std::unique_ptr<ppgso::Mesh> Ground::mesh;
std::unique_ptr<ppgso::Texture> Ground::texture;
std::unique_ptr<ppgso::Shader> Ground::shader;

Ground::Ground() {
    // Scale the default model
    scale *= 1000.0f;

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("ground_texture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("ground.obj");
}

bool Ground::update(Scene &scene, float dt) {

    generateModelMatrix();
    return true;
}

void Ground::render(Scene &scene) {
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



