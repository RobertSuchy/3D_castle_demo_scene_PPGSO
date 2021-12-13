#include <cmath>
#include <glm/glm.hpp>

#include "camera.h"

Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI / 180.0f) * fow;

    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

void Camera::update(float dt) {
//    eyeX = std::sin(glfwGetTime()) * radius;
//    eyeZ = std::cos(glfwGetTime()) * radius;
//    auto speed = 10;
//    age += dt;
//    // priblíženie sa k hradu
//    if (age < 90.0f) {
//        eyeX -= 4.0f * speed;
//        eyeY -= 0.8f * speed;
//        if (eyeX < 501.0f) {
//            age = 90.0f;
//        }
//    }
//    // rotácia okolo hradu
//    else if (age >= 90.0f && !switchScene) {
////        eyeX = std::sin((age * 25) / 180.0f * M_PI) * radius;
////        eyeZ = std::cos((age * 25) / 180.0f * M_PI) * radius;
//        eyeX = std::sin((age * 101.0f) / 180.0f * M_PI) * radius;
//        eyeZ = std::cos((age * 101.0f) / 180.0f * M_PI) * radius;
//        // nastavenie kamery pred bránu
//        if (eyeX > 499.9f && eyeZ > 0.0f) {
//            switchScene = true;
//            eyeX = 200.0f;
//            eyeY = centerY = 10.0f;
//            eyeZ = centerZ = 15.0f;
//        }
//    }
//    // chôdza cez bránu
//    else if (age > 90.0f) {
//        if (eyeX > 110.0f) {
//            eyeX -= 0.1f * speed;
//            eyeY = std::sin(age * 10.0f) * 0.25f + 10.0f;
//        }
//        else {
////            eyeZ += 0.1f;
////            centerZ += 0.1f;
//            // pohľad vpravo
//            if (lookRight) {
//                centerZ -= 1.0f * speed;
//                if (centerZ < -85.0f) {
//                    lookRight = false;
//                }
//            }
//            // pohľad vľavo
//            else if (lookLeft) {
//                centerZ += 1.0f * speed;
//                if (centerZ > 80.0f) {
//                    lookLeft = false;
//                }
//            }
//            // pohyb rovno a vľavo
//            else if (eyeX > 70.0f && eyeZ < 55.0f ) {
//                eyeX -= 0.1f * speed;
//                eyeZ += 0.1f * speed;
//                eyeY = std::sin(age * 10.0f) * 0.25f + 10.0f;
//                centerZ -= 0.075f * speed;
//            }
//            // pohyb rovno
//            else if (eyeX > 10.0f) {
//                eyeX -= 0.1f * speed;
//                eyeY = std::sin(age * 10.0f) * 0.25f + 10.0f;
//            }
//            // pohyb rovno a vpravo
//            else if (eyeX > -50.0f) {
//                eyeX -= 0.1f * speed;
//                eyeZ -= 0.1f * speed;
//                centerZ -= 0.15f * speed;
//                eyeY = std::sin(age * 10.0f) * 0.25f + 10.0f;
//            }
//            else if (lookUp) {
//                centerY += 0.1f;
//                if (centerY > 25.0f) {
//                    lookUp = false;
//                }
//            }
//            else if (centerY >= 10.0f) {
//                centerY -= 0.1f;
//            }
//        }
//    }
//    eyeX = -70;
//    eyeY = 150;
//    eyeZ = 0;

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
