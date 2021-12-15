#include <iostream>
#include <map>
#include <list>

#include <ppgso/ppgso.h>

#include "camera.h"
#include "scene.h"
#include "castle.h"
#include "ground.h"
#include "tree.h"
#include "fireplace.h"
#include "fireplace_shadow.h"
#include "generator.h"
#include "clock.h"
#include "background.h"
#include "flag.h"
#include "bird.h"

const unsigned int SCREEN_SIZE_X = 1920;
const unsigned int SCREEN_SIZE_Y = 1080;

class SceneWindow : public ppgso::Window {
private:
    Scene scene;
    float ratio = float(SCREEN_SIZE_X) / float(SCREEN_SIZE_Y);
    bool animate = true;

    void pushTrees(float positionX, float positionZ) {
        auto tree = std::make_unique<Tree>();
        tree->position.x = positionX;
        tree->position.z = positionZ;
        scene.objects.push_back(move(tree));

        auto tree1 = std::make_unique<Tree>();
        tree1->position.x = -positionX;
        tree1->position.z = positionZ;
        scene.objects.push_back(move(tree1));

        auto tree2 = std::make_unique<Tree>();
        tree2->position.x = positionX;
        tree2->position.z = -positionZ;
        scene.objects.push_back(move(tree2));

        auto tree3 = std::make_unique<Tree>();
        tree3->position.x = -positionX;
        tree3->position.z = -positionZ;
        scene.objects.push_back(move(tree3));
    }

    /*!
     * Reset and initialize the game scene
     * Creating unique smart pointers to objects that are stored in the scene object list
     */
    void initScene() {
        scene.objects.clear();

        // vytvorenie a pridanie kamery do scény
        auto camera = std::make_unique<Camera>(45.0f, ratio, 0.1f, 20000.0f);
        scene.camera = move(camera);

        // pridanie terénu do scény
        auto ground = std::make_unique<Ground>();
        scene.objects.push_back(move(ground));

        // pridanie oblohy do scény
        auto background = std::make_unique<Background>();
        scene.objects.push_back(move(background));

        // pridanie hradu do scény
        auto castle = std::make_unique<Castle>();
        castle->position.x = 50.0f;
        scene.objects.push_back(move(castle));

        // pridanie stromov do scény - procedurálne generované
        float positionX, positionZ;
        for (int j = 0; j < 50; j++) {
            positionX = glm::linearRand(250.0f, 850.0f);
            positionZ = glm::linearRand(250.0f, 850.0f);
            pushTrees(positionX, positionZ);

            positionX = glm::linearRand(0.0f, 200.0f);
            positionZ = glm::linearRand(250.0f, 1750.0f);
            pushTrees(positionX, positionZ);

            positionX = glm::linearRand(250.0f, 1750.0f);
            positionZ = glm::linearRand(0.0f, 200.0f);
            pushTrees(positionX, positionZ);
        }

        // pridanie vtáka do scény
        auto bird = std::make_unique<Bird>();
        scene.objects.push_back(move(bird));

        // pridanie ohniska do scény
        auto fireplace = std::make_unique<Fireplace>();
        fireplace->position.z = -75;
        scene.objects.push_back(move(fireplace));

        // pridanie tieňa ohniska do scény
        auto fireplaceShadow = std::make_unique<FireplaceShadow>();
        fireplaceShadow->position.y = 2;
        fireplaceShadow->position.z = -80;
        scene.objects.push_back(move(fireplaceShadow));

        // pridanie generátora do scény
        auto generator = std::make_unique<Generator>();
        scene.objects.push_back(move(generator));

        // pridanie vlajky do scény
        auto flag = std::make_unique<Flag>();
        flag->position.x = -50.0f;
        flag->position.y = 90.0f;
        flag->position.z = 105.0f;
        scene.objects.push_back(move(flag));

        // pridanie hodín do scény
        auto clock = std::make_unique<Clock>();
        clock->position.x = -98.5f;
        clock->position.y = 27.75f;
        clock->position.z = -39.75f;
        scene.objects.push_back(move(clock));
    }

public:
    SceneWindow() : Window{"castle_demo_scene", SCREEN_SIZE_X, SCREEN_SIZE_Y} {
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        initScene();
    }

    void onIdle() override {
        static auto time = (float) glfwGetTime();
        float dt = animate ? (float) glfwGetTime() - time : 0;
        time = (float) glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.update(dt);
        scene.render();
    }
};

int main() {
    SceneWindow window;

    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}
