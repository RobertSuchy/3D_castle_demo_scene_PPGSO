#include <glm/gtc/random.hpp>
#include "spear.h"
#include "castle.h"
#include "wall_particle.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Spear::mesh;
std::unique_ptr<ppgso::Texture> Spear::texture;
std::unique_ptr<ppgso::Shader> Spear::shader;

Spear::Spear() {
    scale *= 5.0f;
    size = 6.35f * scale.x;
    speed = 500.0f;
    throwDistance = 1975.0f;
    rotation.x = M_PI / 8;

    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("spear_texture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("spear.obj");
}

bool Spear::update(Scene &scene, float dt) {
    age += dt;
    if (age > 4.6f) {
        return false;
    }

    if (flyingSpear) {
        rotation.x -= dt / 5;
        position.y = speed * age * std::sin(M_PI / 8) - 9.81 * 9 * pow(age, 2) / 2;
        position.z = throwDistance - speed * age * std::cos(M_PI / 8);

        for (auto &obj: scene.objects) {
            if (obj.get() == this) continue;

            auto castle = dynamic_cast<Castle *>(obj.get());
            if (!castle) continue;

            if (distance(position, obj->position) < obj->scale.x * 1730 + scale.x) {
                flyingSpear = false;
                for (int i = 0; i < 20; i++) {
                    float offset = glm::linearRand(2.5f, 3.5f);
                    float posZ = size/2.0f * -std::sin(rotation.x * M_PI) - offset;
                    float posY = size/2.0f * std::cos(rotation.x * M_PI);
                    auto wallParticle = std::make_unique<WallParticle>();
                    wallParticle->position.x = position.x;
                    wallParticle->position.y = position.y - posY;
                    wallParticle->position.z = position.z - posZ;
                    scene.objects.push_back(move(wallParticle));
                }
            }
        }
    }

    generateModelMatrix();

    return true;
}

void Spear::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}

