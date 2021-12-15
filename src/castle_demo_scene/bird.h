#pragma once
#include <ppgso/ppgso.h>

#include "object.h"

class Bird final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;

    struct Keyframe {
        float age;
        glm::vec3 pos;
        glm::vec3 rot;
        glm::vec3 scl;
        float time;
    };

    std::list<Keyframe> keyframes;

public:Bird();

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
