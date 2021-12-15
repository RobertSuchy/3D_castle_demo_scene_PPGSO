#pragma once
#include <ppgso/ppgso.h>

#include "object.h"
#include "hour_hand.h"

class MinuteHand final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    std::unique_ptr<HourHand> child;

public:MinuteHand();

    /*!
     * Update player position considering keyboard inputs
     * @param scene Scene to update
     * @param dt Time delta
     * @return true to delete the object
     */

    bool update(Scene &scene, float dt) override;

//    bool update(Scene &scene, float dt, glm::vec3 rotationOfParent);
    bool update(Scene &scene, float dt, glm::mat4 modelMatrixOfParent);

    /*!
     * Render player
     * @param scene Scene to render in
     */
    void render(Scene &scene) override;
};
