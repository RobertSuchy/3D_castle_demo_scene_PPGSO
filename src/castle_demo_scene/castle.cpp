#include "castle.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include <shaders/convolution_vert_glsl.h>
#include <shaders/convolution_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Castle::mesh;
std::unique_ptr<ppgso::Texture> Castle::texture;
std::unique_ptr<ppgso::Shader> Castle::shader;

Castle::Castle() {
    scale *= 0.1f;

    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("castle_texture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("castle.obj");
}

bool Castle::update(Scene &scene, float dt) {
    age += dt;
    if (age > 109.0f) {
        shader = std::make_unique<ppgso::Shader>(convolution_vert_glsl, convolution_frag_glsl);
    }
    generateModelMatrix();
    return true;
}

void Castle::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    mesh->render();
}
