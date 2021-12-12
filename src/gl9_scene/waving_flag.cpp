#include "waving_flag.h"
#include <shaders/texture_frag_glsl.h>
#include <shaders/texture_vert_glsl.h>

std::unique_ptr<ppgso::Texture> WavingFlag::texture;
std::unique_ptr<ppgso::Shader> WavingFlag::shader;

WavingFlag::WavingFlag(const glm::vec3 controlPoints[4][4]) {
    scale *= 8.0f;
    position.x = -88;
    position.y = 106;
    position.z = 105;
    rotation.x = M_PI;

    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("flag_texture.bmp"));

// Generate Bezier patch points and incidences
    unsigned int PATCH_SIZE = 10;
    for (unsigned int i = 0; i < PATCH_SIZE; i++) {
        for (unsigned int j = 0; j < PATCH_SIZE; j++) {

            glm::vec3 u[4];
            for (int k = 0; k < 4; k++) {
                u[k] = bezierPoint(controlPoints[k], j / (float) (PATCH_SIZE-1));
            }

            vertices.push_back(bezierPoint(u, i / (float) (PATCH_SIZE-1)));

            texCoords.push_back({j / (float) (PATCH_SIZE-1), i / (float) (PATCH_SIZE-1)});
        }
    }
    // Generate indices
    for (unsigned int i = 1; i < PATCH_SIZE; i++) {
        for (unsigned int j = 1; j < PATCH_SIZE; j++) {
            mesh.push_back({
                                   PATCH_SIZE * i + j - 1,
                                   PATCH_SIZE * i + j,
                                   PATCH_SIZE * (i - 1) + j
                           });
            mesh.push_back({
                                   PATCH_SIZE * i + j - 1,
                                   PATCH_SIZE * (i - 1) + j,
                                   PATCH_SIZE * (i - 1) + j - 1
                           });

        }
    }

    // Copy data to OpenGL
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Copy positions to gpu
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Set vertex program inputs
    auto position_attrib = shader->getAttribLocation("Position");
    glEnableVertexAttribArray(position_attrib);
    glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Copy texture positions to gpu
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);

    // Set vertex program inputs
    auto texCoord_attrib = shader->getAttribLocation("TexCoord");
    glEnableVertexAttribArray(texCoord_attrib);
    glVertexAttribPointer(texCoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Copy indices to gpu
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.size() * sizeof(face), mesh.data(), GL_STATIC_DRAW);

}

glm::vec3 WavingFlag::bezierPoint(const glm::vec3 *controlPoints, float t) {
    glm::vec3 points[4] = {controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3]};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            points[j] = glm::vec3{points[j].x + (points[j + 1].x - points[j].x) * t,
                                  points[j].y + (points[j + 1].y - points[j].y) * t,
                                  points[j].z + (points[j + 1].z - points[j].z) * t};
        }
    }
    return {points[0]};
}

bool WavingFlag::update(Scene &scene, float dt) {
    modelMatrix =
            glm::translate(glm::mat4{1.0f}, position)
            * glm::rotate(glm::mat4{1.0f}, rotation.x, glm::vec3{1, 0, 0})
//            * glm::rotate(glm::mat4{1.0f}, rotation.y, glm::vec3{0, 1, 0})
//            * glm::rotate(glm::mat4{1.0f}, rotation.z, glm::vec3{0, 0, 1})
            * glm::scale(glm::mat4{1.0f}, scale);
    return true;
}

void WavingFlag::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);

    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // Set model position
    shader->setUniform("ModelMatrix", modelMatrix);

    // Bind texture
    shader->setUniform("Texture", *texture);

    glBindVertexArray(vao);
    // TODO: Use correct rendering mode to draw the result
    //glDrawElements(??);
    glDrawElements(GL_TRIANGLES, (GLsizei) mesh.size() * sizeof(face), GL_UNSIGNED_INT, 0);

    glDisable(GL_CULL_FACE);
}
