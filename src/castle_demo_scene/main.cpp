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
#include "generator.h"
#include "background.h"
#include "flag.h"
#include "spear.h"

const unsigned int SIZE = 1024;

/*!
 * Custom windows for our simple game
 */
class SceneWindow : public ppgso::Window {
private:
    Scene scene;
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
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 15000.0f);
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

        // pridanie ohniska do scény
        auto fireplace = std::make_unique<Fireplace>();
        fireplace->position.z = -75;
        scene.objects.push_back(move(fireplace));

        // pridanie generátora do scény
        auto generator = std::make_unique<Generator>();
        scene.objects.push_back(move(generator));
        auto flag = std::make_unique<Flag>();
        flag->position.x = -50;
        flag->position.y = 90;
        flag->position.z = 105;
        scene.objects.push_back(move(flag));

        // pridanie oštepu do scény
        auto spear = std::make_unique<Spear>();
        spear->position.x = -55;
        scene.objects.push_back(move(spear));
    }

public:
    /*!
     * Construct custom game window
     */
    SceneWindow() : Window{"castle_demo_scene", SIZE, SIZE} {
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        initScene();
    }

//    /*!
//     * Handles pressed key when the window is focused
//     * @param key Key code of the key being pressed/released
//     * @param scanCode Scan code of the key being pressed/released
//     * @param action Action indicating the key state change
//     * @param mods Additional modifiers to consider
//     */
//    void onKey(int key, int scanCode, int action, int mods) override {
//        scene.keyboard[key] = action;
//
//        // Reset
//        if (key == GLFW_KEY_R && action == GLFW_PRESS) {
//            initScene();
//        }
//
//        // Pause
//        if (key == GLFW_KEY_P && action == GLFW_PRESS) {
//            animate = !animate;
//        }
//    }
//
//    /*!
//     * Handle cursor position changes
//     * @param cursorX Mouse horizontal position in window coordinates
//     * @param cursorY Mouse vertical position in window coordinates
//     */
//    void onCursorPos(double cursorX, double cursorY) override {
//        scene.cursor.x = cursorX;
//        scene.cursor.y = cursorY;
//    }
//
//    /*!
//     * Handle cursor buttons
//     * @param button Mouse button being manipulated
//     * @param action Mouse bu
//     * @param mods
//     */
//    void onMouseButton(int button, int action, int mods) override {
//        if (button == GLFW_MOUSE_BUTTON_LEFT) {
//            scene.cursor.left = action == GLFW_PRESS;
//
//            if (scene.cursor.left) {
//                // Convert pixel coordinates to Screen coordinates
//                double u = (scene.cursor.x / width - 0.5f) * 2.0f;
//                double v = -(scene.cursor.y / height - 0.5f) * 2.0f;
//
//                // Get mouse pick vector in world coordinates
//                auto direction = scene.camera->cast(u, v);
////                auto position = scene.camera->position;
//
//                // Get all objects in scene intersected by ray
////                auto picked = scene.intersect(position, direction);
//
//                // Go through all objects that have been picked
//                for (auto &obj: picked) {
//                    // Pass on the click event
//                    obj->onClick(scene);
//                }
//            }
//        }
//        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
//            scene.cursor.right = action == GLFW_PRESS;
//        }
//    }

    /*!
     * Window update implementation that will be called automatically from pollEvents
     */
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
