#pragma once
#include <ppgso/ppgso.h>

#include "object.h"
#include "scene.h"


class WavingFlag final : public Object {
private:
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    float age{0.0f};

    std::vector<glm::vec3> vertices;

    // Texture coordinates
    std::vector<glm::vec2> texCoords;

    // Define our face using indexes to 3 vertices
    struct face {
        GLuint v0, v1, v2;
    };

    // Define our mesh as collection of faces
    std::vector<face> mesh;

    // These will hold the data and object buffers
    GLuint vao, vbo, tbo, ibo;
    glm::mat4 modelMatrix{1.0f};

    glm::vec3 bezierPoint(const glm::vec3 controlPoints[4], float t);


public:
    WavingFlag(const glm::vec3 controlPoints[4][4]);

//    glm::vec3 rotation{-ppgso::PI/2, 0, 0};

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


