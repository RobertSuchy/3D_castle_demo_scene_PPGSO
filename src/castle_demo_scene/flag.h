#pragma once
#include <ppgso/ppgso.h>

#include "object.h"
#include "scene.h"

class Flag final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    float age{0.0f};

    glm::vec3 controlPoints[4][4] {
            {{-1.5, 1,   0}, {-0.75, 1,   0}, {.75, 1,   0}, {1.5, 1,   0},},
            {{-1.5, .5,  0}, {-0.75, .5,  0}, {.75, .5,  0}, {1.5, .5,  0},},
            {{-1.5, -.5, 0}, {-0.75, -.5, 0}, {.75, -.5, 0}, {1.5, -.5, 0},},
            {{-1.5, -1,  0}, {-0.75, -1,  0}, {.75, -1,  0}, {1.5, -1,  0},},
    };

public:
    Flag();

    /*!
     * Update player position considering keyboard inputs
     * @param scene Scene to update
     * @param dt Time delta
     * @return true to delete the object
     */
    bool update(Scene &scene, float dt) override;

    /*!
     * Render player
     * @param scene Scene to render in
     */
    void render(Scene &scene) override;
};