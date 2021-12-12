// Example gl_scene
// - Introduces the concept of a dynamic scene of objects
// - Uses abstract object interface for Update and Render steps
// - Creates a simple game scene with Player, Asteroid and Space objects
// - Contains a generator object that does not render but adds Asteroids to the scene
// - Some objects use shared resources and all object deallocations are handled automatically
// - Controls: LEFT, RIGHT, "R" to reset, SPACE to fire

#include <iostream>
#include <map>
#include <list>

#include <ppgso/ppgso.h>

#include "camera.h"
#include "scene.h"
#include "castle.h"
#include "space.h"
#include "ground.h"
#include "tree.h"
#include "fireplace.h"
#include "generator.h"
#include "background.h"
#include "flag.h"

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

        // Create a camera
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 15000.0f);
        scene.camera = move(camera);

        // Add castle to the scene
        auto castle = std::make_unique<Castle>();
        scene.objects.push_back(move(castle));

        // Add ground to the scene
        auto ground = std::make_unique<Ground>();
        scene.objects.push_back(move(ground));

        // Add trees to the scene
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

        // Add fireplace to the scene
        auto fireplace = std::make_unique<Fireplace>();
        fireplace->position.x = -50;
        fireplace->position.z = -75;
        scene.objects.push_back(move(fireplace));

        auto background = std::make_unique<Background>();
        scene.objects.push_back(move(background));

        auto generator = std::make_unique<Generator>();
        //generator->position.y = 10;
        scene.objects.push_back(move(generator));

        auto flag = std::make_unique<Flag>();
        flag->position.x = -100;
        flag->position.y = 90;
        flag->position.z = 105;
        scene.objects.push_back(move(flag));
    }

public:
    /*!
     * Construct custom game window
     */
    SceneWindow() : Window{"gl9_scene", SIZE, SIZE} {
        //hideCursor();
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

        // Initialize OpenGL state
        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable polygon culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        initScene();
    }

    /*!
     * Handles pressed key when the window is focused
     * @param key Key code of the key being pressed/released
     * @param scanCode Scan code of the key being pressed/released
     * @param action Action indicating the key state change
     * @param mods Additional modifiers to consider
     */
    void onKey(int key, int scanCode, int action, int mods) override {
        scene.keyboard[key] = action;

        // Reset
        if (key == GLFW_KEY_R && action == GLFW_PRESS) {
            initScene();
        }

        // Pause
        if (key == GLFW_KEY_P && action == GLFW_PRESS) {
            animate = !animate;
        }
    }

    /*!
     * Handle cursor position changes
     * @param cursorX Mouse horizontal position in window coordinates
     * @param cursorY Mouse vertical position in window coordinates
     */
    void onCursorPos(double cursorX, double cursorY) override {
        scene.cursor.x = cursorX;
        scene.cursor.y = cursorY;
    }

    /*!
     * Handle cursor buttons
     * @param button Mouse button being manipulated
     * @param action Mouse bu
     * @param mods
     */
    void onMouseButton(int button, int action, int mods) override {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            scene.cursor.left = action == GLFW_PRESS;

            if (scene.cursor.left) {
                // Convert pixel coordinates to Screen coordinates
                double u = (scene.cursor.x / width - 0.5f) * 2.0f;
                double v = -(scene.cursor.y / height - 0.5f) * 2.0f;

                // Get mouse pick vector in world coordinates
                auto direction = scene.camera->cast(u, v);
                auto position = scene.camera->position;

                // Get all objects in scene intersected by ray
                auto picked = scene.intersect(position, direction);

                // Go through all objects that have been picked
                for (auto &obj: picked) {
                    // Pass on the click event
                    obj->onClick(scene);
                }
            }
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            scene.cursor.right = action == GLFW_PRESS;
        }
    }

    /*!
     * Window update implementation that will be called automatically from pollEvents
     */
    void onIdle() override {
        // Track time
        static auto time = (float) glfwGetTime();

        // Compute time delta
        float dt = animate ? (float) glfwGetTime() - time : 0;

        time = (float) glfwGetTime();

        // Set gray background
        glClearColor(.5f, .5f, .5f, 0);
        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update and render all objects
        scene.update(dt);
        scene.render();
    }
};

int main() {
    // Initialize our window
    SceneWindow window;

    // Main execution loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}
