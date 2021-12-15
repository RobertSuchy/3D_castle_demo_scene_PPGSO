#pragma once

#include <ppgso/ppgso.h>

#include "object.h"

class Bird final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;

    float age{0.0f};

    int currentKeyframeIndex = 0;

    struct Keyframe {
        float age;
        glm::vec3 pos;
        glm::vec3 rot;
        glm::vec3 scl;
    };

    std::vector<Keyframe> keyframes = {
            {
                    3.3f,
                    glm::vec3{3450.0f, 1000.0f, 0.0f},
                    glm::vec3{0.0f, 0.0f, -M_PI / 2.0f},
                    scale * 35.0f
            },
            {
                    6.6f,
                    glm::vec3{2450.0f, 600.0f, 0.0f},
                    glm::vec3{0.0f, M_PI / 4.0f, -M_PI / 2.0f},
                    scale * 35.0f
            },
            {
                    10.0f,
                    glm::vec3{1450.0f, 400.0f, 0.0f},
                    glm::vec3{0.0f, -M_PI / 4.0f, -M_PI / 2.0f},
                    scale * 35.0f
            },
            {
                    14.0f,
                    glm::vec3{250.0f, 150.0f, 0.0f},
                    glm::vec3{0.0f, 0.0f, -M_PI / 2.0f},
                    scale * 35.0f
            },
            {
                    0,
                    glm::vec3{0.0f, 300.0f, -500.0f},
                    glm::vec3{0.0f, M_PI / 4.0f, M_PI},
                    scale * 35.0f
            }
    };


public:
    Bird();

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
