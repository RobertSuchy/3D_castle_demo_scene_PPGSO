#include <cmath>
#include <glm/glm.hpp>

#include "camera.h"


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI / 180.0f) * fow;

    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

void Camera::update(float dt) {
//        eyeX = std::sin(glfwGetTime()) * radius;
//        eyeZ = std::cos(glfwGetTime()) * radius;
    auto speed = 100;
    age += dt;
    if (age < 90.0f) {
        eyeX -= 1.0f * speed;
        eyeY -= 0.20f * speed;
        if (eyeX < 501.0f) {
            age = 90.0f;
        }
    }
    else if (age >= 90.0f && !switchScene) {
//        eyeX = std::sin((age * 13) / 180.0f * M_PI) * radius;
//        eyeZ = std::cos((age * 13) / 180.0f * M_PI) * radius;
        eyeX = std::sin((age * 101.0f) / 180.0f * M_PI) * radius;
        eyeZ = std::cos((age * 101.0f) / 180.0f * M_PI) * radius;
        if (eyeX > 499.9f && eyeZ > 0.0f) {
            switchScene = true;
            eyeX = 200.0f;
            eyeY = 10.0f;
            eyeZ = centerZ = 15.0f;
        }
    }
    else if (age > 90.0f) {
        if (eyeX > 100.0f) {
            eyeX -= 0.1f;
            eyeY = std::sin(age * 10.0f) * 0.25f + 10.0f;
        }
        else {
//            eyeZ += 0.1f;
//            centerZ += 0.1f;
            if (centerX < 90.0f) {
                centerX += 0.25f;
                centerZ -= 0.25f;
            }
        }
    }
//    eyeX = -70;
//    eyeY = 150;
//    eyeZ = 0;
//
//    viewMatrix = lookAt(glm::vec3(eyeX, eyeY, eyeZ), glm::vec3(-50.0, 50.0, -70.0), glm::vec3(0.0, 1.0, 0.0));
    viewMatrix = lookAt(glm::vec3(eyeX, eyeY, eyeZ), glm::vec3(centerX, centerY, centerZ), glm::vec3(0.0, 1.0, 0.0));
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
