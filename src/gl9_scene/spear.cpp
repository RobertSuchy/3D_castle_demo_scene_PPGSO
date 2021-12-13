#include <glm/gtc/random.hpp>
#include "spear.h"
#include "ground.h"
#include "explosion.h"
#include "castle.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

// Static resources
std::unique_ptr<ppgso::Mesh> Spear::mesh;
std::unique_ptr<ppgso::Texture> Spear::texture;
std::unique_ptr<ppgso::Shader> Spear::shader;

Spear::Spear() {
    // Set random scale speed and rotation
//    scale *= glm::linearRand(10.0f, 30.0f);
    scale *= 5.0f;
    speed = {glm::linearRand(-2.0f, 2.0f), glm::linearRand(-500.0f, -1000.0f), 0.0f};
    rotation.x = M_PI/8;
    rotMomentum = glm::ballRand(ppgso::PI);

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("spear_texture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("spear.obj");
}

bool Spear::update(Scene &scene, float dt) {
    // Count time alive
    age += dt;

//    position.y = 700*age*std::sin(M_PI/8) - 9.81*17* age*age/2;
//    position.z = 2000.0f - 700*age*std::cos(M_PI/8);
//    std::cout<<position.y<<position.z<<std::endl;


    if (movicek) {
        rotation.x -= dt/5;
        position.y = 500*age*std::sin(M_PI/8) - 9.81*9* age*age/2;
        position.z = 1975.0f - 500*age*std::cos(M_PI/8);
    }



    // Animate position according to time
//    position += speed * (dt/2);

    // Rotate the object
//    rotation += rotMomentum * (dt / 5);


    // Collide with scene
    for (auto &obj: scene.objects) {
        // Ignore self in scene
        if (obj.get() == this) continue;

        // We only need to collide with asteroids and projectiles, ignore other objects
//        auto spear = dynamic_cast<Spear*>(obj.get()); // dynamic_pointer_cast<Asteroid>(obj);
        auto castle = dynamic_cast<Castle*>(obj.get()); //dynamic_pointer_cast<Projectile>(obj);
        if (!castle) {
//            std::cout<<position.y<<position.z<<std::endl;
            continue;
        }

        // When colliding with other asteroids make sure the object is older than .5s
        // This prevents excessive collisions when asteroids explode.


//        bool collisionX = position.x + scale.x >= obj->position.x &&
//                obj->position.x + obj->scale.x >= position.x;
//        // collision y-axis?
//        bool collisionY = position.y + scale.y >= obj->position.y &&
//                obj->position.y + obj->scale.y >= position.y;
//        // collision only if on both axes
//        if (collisionX && collisionY) {
//            std::cout<<position.y<<" "<<position.z<<std::endl;
//            return false;
//        }
//        return collisionX && collisionY;
//         Compare distance to approximate size of the asteroid estimated from scale.
        if (distance(position, obj->position) < (obj->scale.x*1730 + scale.x) * 1.0f) {
//            std::cout<<position.y<<" "<<position.z<<std::endl;
            movicek = false;
//            int pieces = 3;
//
//            // Too small to split into pieces
//            if (scale.y < 0.5) pieces = 0;

            // The projectile will be destroyed
//            if (projectile) projectile->destroy();

            // Generate smaller asteroids
//            explode(scene, (obj->position + position) / 2.0f, (obj->scale + scale) / 2.0f);
//            if (asteroid && age < 2.0f){
//                return false;
//            }

//            reproduce(scene);

//            // Destroy self
//            return false;
        }
    }

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Spear::reproduce(Scene &scene) {
    // Generate smaller asteroids
    for (int i = 0; i < 5; i++) {
        auto obj = std::make_unique<Spear>();
        obj->position = position;
//        obj->position.y += 1000.0f;
        obj->position.x += glm::linearRand(-1000.0f, 1000.0f);
        obj->position.z += glm::linearRand(-1000.0f, 1000.0f);
        obj->scale = scale / 5.0f;
        scene.objects.push_back(move(obj));
//        auto asteroid = std::make_unique<Asteroid>();
//        asteroid->speed = speed + glm::vec3(glm::linearRand(-3.0f, 3.0f), glm::linearRand(0.0f, -5.0f), 0.0f);;
//        asteroid->position = position;
//        asteroid->rotMomentum = rotMomentum;
//        float factor = (float) 3 / 2.0f;
//        asteroid->scale = scale / factor;
//        scene.objects.push_back(move(asteroid));
    }
}


void Spear::explode(Scene &scene, glm::vec3 explosionPosition, glm::vec3 explosionScale) {
    // Generate explosion
    auto explosion = std::make_unique<Explosion>();
    explosion->position = explosionPosition;
    explosion->scale = explosionScale;
    explosion->speed = speed / 2.0f;
    scene.objects.push_back(move(explosion));
}

void Spear::render(Scene &scene) {
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

//void Asteroid::onClick(Scene &scene) {
//    std::cout << "Asteroid clicked!" << std::endl;
//    explode(scene, position, {10.0f, 10.0f, 10.0f}, 0);
//    age = 10000;
//}

