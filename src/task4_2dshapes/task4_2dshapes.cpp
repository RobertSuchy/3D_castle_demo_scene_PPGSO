// Task 5 - Draw a 2D shape using polygons and animate it
//        - Encapsulate the shape using a class
//        - Use color_vert/frag shader to display the polygon
//        - Animate the object position, rotation and scale.

#include <iostream>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <ppgso/ppgso.h>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

const unsigned int SIZE = 512;

// Object to represent 2D OpenGL shape
class Shape {
private:
    // 2D vectors define points/vertices of the shape
    // TODO: Define your shape points
    std::vector<glm::vec3> vertices = {
            {0,   0, 0},
            {0.04, 0, 0},
            {0.04, 0.04,   0},
            {0,   0.04,   0},
            {0.03,   -0.03,   0},
            {0.14,   -0.03,   0},
            {0.14,   0.03,   0},
            {0.03,   0.03,   0},
    };

    // Structure representing a triangular face, usually indexes into vertices
    struct Face {
        // TODO: Define your face structure
        GLuint  a, b, c;
    };

    // Indices define triangles that index into vertices
    // TODO: Define your mesh indices
    std::vector<Face> mesh = {
            {0, 1, 3},
            {1, 2, 3},
            {4, 5, 7},
            {5, 6, 7},
    };

    // Program to associate with the object
    ppgso::Shader program = {color_vert_glsl, color_frag_glsl};

    // These will hold the data and object buffers
    GLuint vao, vbo, cbo, ibo;
    glm::mat4 modelMatrix{1.0f};
public:
    // Public attributes that define position, color ..
    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{1, 0, 1};
    glm::vec3 color{1, 0, 0};

    // Initialize object data buffers
    Shape() {
        // Copy data to OpenGL
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Copy positions to gpu
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

        // Set vertex program inputs
        auto position_attrib = program.getAttribLocation("Position");
        glEnableVertexAttribArray(position_attrib);
        glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Copy mesh indices to gpu
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.size() * sizeof(Face), mesh.data(), GL_STATIC_DRAW);

        // Set projection matrices to identity
        program.setUniform("ProjectionMatrix", glm::mat4{1.0f});
        program.setUniform("ViewMatrix", glm::mat4{1.0f});
    };

    // Clean up
    ~Shape() {
        // Delete data from OpenGL
        glDeleteBuffers(1, &ibo);
        glDeleteBuffers(1, &cbo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    // Set the object transformation matrix
    void update() {
        // TODO: Compute transformation by scaling, rotating and then translating the shape
        modelMatrix = glm::translate(glm::mat4 {1.0f}, position)
                      * glm::rotate(glm::mat4 {1.0f}, rotation.z, glm::vec3 {0, 0, 1});
//                      * glm::scale(glm::mat4 {1.0f}, scale);
    }

    // Draw polygons
    void render() {
        // Update transformation and color uniforms in the shader
        program.use();
        program.setUniform("OverallColor", color);
        program.setUniform("ModelMatrix", modelMatrix);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, (GLsizei) mesh.size() * 3, GL_UNSIGNED_INT, 0);
    };
};

class ShapeWindow : public ppgso::Window {
private:
    Shape shape1, shape2;
    int multiple = 1;
public:
    ShapeWindow() : Window{"task4_2dshapes", SIZE, SIZE} {
        shape1.color = {1, 1, 1};
        shape2.color = {1, 1, 1};
    }

    void onIdle() {
        // Set gray background
        glClearColor(0.0f, 168.1f/255.0f, 251.1f/255.0f, 0.8f);
        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Move and Render shape\    // Get time for animation
        auto t = (float) glfwGetTime();

        // TODO: manipuate shape1 and shape2 position to rotate clockwise
        shape1.position[0] -= 0.001;
//        shape1.position[1] = -shape1.position[1] + 0.75;
        shape2.position[0] -= 0.001;
//        shape2.position[1] = -shape2.position[1] + 0.25;

        // Manipulate rotation of the shape
        shape1.rotation.z = t * 5.0f * multiple;
        shape2.rotation.z = -t * 5.0f * multiple;
        multiple *= -1;

        // Manipulate shape size
//        shape1.scale = {-sin(t), -sin(t), -1};
//        shape2.scale = {cos(t/2), cos(t/2), 1};

        // Update and render each shape
        shape1.update();
        shape2.update();

        shape1.render();
        shape2.render();
    }
};

int main() {
    // Create our window
    auto window = ShapeWindow{};

    // Main execution loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}
