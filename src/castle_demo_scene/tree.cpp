#include "tree.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Tree::mesh;
std::unique_ptr<ppgso::Texture> Tree::texture;
std::unique_ptr<ppgso::Shader> Tree::shader;

Tree::Tree() {
    scale *= 0.1f;

    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("tree_texture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("tree.obj");
}

bool Tree::update(Scene &scene, float dt) {

    generateModelMatrix();
    return true;
}

void Tree::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}


