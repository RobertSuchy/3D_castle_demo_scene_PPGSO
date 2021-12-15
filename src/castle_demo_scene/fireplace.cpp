#include "fireplace.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Fireplace::mesh;
std::unique_ptr<ppgso::Texture> Fireplace::texture;
std::unique_ptr<ppgso::Shader> Fireplace::shader;

Fireplace::Fireplace() {
    scale *= 0.2f;

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

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}
