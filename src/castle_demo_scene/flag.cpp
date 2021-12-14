#include "flag.h"
#include "waving_flag.h"
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include <cmath>

std::unique_ptr<ppgso::Mesh> Flag::mesh;
std::unique_ptr<ppgso::Texture> Flag::texture;
std::unique_ptr<ppgso::Shader> Flag::shader;

Flag::Flag() {
    scale.y *= 50.0f;

    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("stars.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
}

bool Flag::update(Scene &scene, float dt) {
    age += dt;
    controlPoints[0][1].z = std::cos(age*2)/2;
    controlPoints[0][2].z = std::sin(age*2)/2;
    controlPoints[0][3].z = std::cos(age*2)/4;

    controlPoints[1][1].z = std::sin(age*2)/2;
    controlPoints[1][2].z = std::cos(age*2)/2;
    controlPoints[1][3].z = std::sin(age*2)/4;

    controlPoints[2][1].z = std::cos(age*2)/2;
    controlPoints[2][2].z = std::sin(age*2)/2;
    controlPoints[2][3].z = std::cos(age*2)/4;

    controlPoints[3][1].z = std::sin(age*2)/2;
    controlPoints[3][2].z = std::cos(age*2)/2;
    controlPoints[3][3].z = std::sin(age*2)/4;

    WavingFlag wavingFlag{controlPoints};
    wavingFlag.update(scene, dt);
    wavingFlag.render(scene);

    generateModelMatrix();

    return true;
}

void Flag::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    mesh->render();
}

