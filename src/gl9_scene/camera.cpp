#include <cmath>
#include <glm/glm.hpp>

#include "camera.h"


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI / 180.0f) * fow;

    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

void Camera::update(float dt) {
//        camX = std::sin(glfwGetTime()) * radius;
//        camZ = std::cos(glfwGetTime()) * radius;
    auto speed = 100;
    age += dt;
    if (age < 90.0f) {
        camX -= 1.0f * speed;
        camY -= 0.20f * speed;
        if (camX < 501.0f) {
            age = 90.0f;
        }
    }
    else if (age >= 90.0f && !switchScene) {
        camX = std::sin((age * 13) / 180.0f * M_PI) * radius;
        camZ = std::cos((age * 13) / 180.0f * M_PI) * radius;
        if (camX > 499.9f && camZ > 0) {
            switchScene = true;
            camX = 200;
            camY = 10;
            camZ = 15;
        }
    }
    else if ( age > 91.0f) {
        camX -= 0.1;
        camY = std::sin(age * 10) * 0.25 + 10;
    }
//    camX = -70;
//    camY = 150;
//    camZ = 0;
//
//    viewMatrix = lookAt(glm::vec3(camX, camY, camZ), glm::vec3(-50.0, 50.0, -70.0), glm::vec3(0.0, 1.0, 0.0));
    viewMatrix = lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

glm::vec3 Camera::cast(double u, double v) {
    // Create point in Screen coordinates
    glm::vec4 screenPosition{u, v, 0.0f, 1.0f};

    // Use inverse matrices to get the point in world coordinates
    auto invProjection = glm::inverse(projectionMatrix);
    auto invView = glm::inverse(viewMatrix);

    // Compute position on the camera plane
    auto planePosition = invView * invProjection * screenPosition;
    planePosition /= planePosition.w;

    // Create direction vector
    auto direction = glm::normalize(planePosition - glm::vec4{position, 1.0f});
    return glm::vec3{direction};
}
