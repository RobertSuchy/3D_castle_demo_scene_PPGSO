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
    age += dt * 1.0;

    // priblíženie sa k hradu
//    if (age <= approachTime) {
//        points = {
//                glm::vec3 {radius + 3000.0f, 1000.0f, 0.0f},
//                glm::vec3 {radius + 2000.0f, 600.0f, 0.0f},
//                glm::vec3 {radius + 1000.0f, 400.0f, 0.0f},
//                glm::vec3 {radius, 250.0f, 0.0f}
//        };
//        eye = bezierPoint(points, ((float) age) / approachTime);
//    }
//    // rotácia okolo hradu 1/4
//    else if (age <= approachTime + quarterTime) {
//        points = {
//                glm::vec3 {radius, 250.0f, 0.0f},
//                glm::vec3 {radius * std::sin(M_PI / 3.0f), 250.0f, -radius * std::sin(M_PI / 6.0f)},
//                glm::vec3 {radius * std::sin(M_PI / 6.0f), 250.0f, -radius * std::sin(M_PI / 3.0f)},
//                glm::vec3 {0.0f, 250.0f, -radius}
//        };
//        eye = bezierPoint(points, ((float) age - approachTime) / quarterTime);
//    }
//    // rotácia okolo hradu 2/4
//    else if (age <= approachTime + 2 * quarterTime) {
//        points = {
//                glm::vec3 {0.0f, 250.0f, -radius},
//                glm::vec3 {-radius * std::sin(M_PI / 6.0f), 250.0f, -radius * std::sin(M_PI / 3.0f)},
//                glm::vec3 {-radius * std::sin(M_PI / 3.0f), 250.0f, -radius * std::sin(M_PI / 6.0f)},
//                glm::vec3 {-radius, 250.0f, 0.0f}
//        };
//        eye = bezierPoint(points, ((float) age - (approachTime + quarterTime)) / quarterTime);
//    }
//    // rotácia okolo hradu 3/4
//    else if (age <= approachTime + 3 * quarterTime) {
//        points = {
//                glm::vec3 {-radius, 250.0f, 0.0f},
//                glm::vec3 {-radius * std::sin(M_PI / 3.0f), 250.0f, radius * std::sin(M_PI / 6.0f)},
//                glm::vec3 {-radius * std::sin(M_PI / 6.0f), 250.0f, radius * std::sin(M_PI / 3.0f)},
//                glm::vec3 {0.0f, 250.0f, radius}
//        };
//        eye = bezierPoint(points, ((float) age - (approachTime + 2 * quarterTime)) / quarterTime);
//    }
//    // rotácia okolo hradu 4/4
//    else if (age <= approachTime + 4 * quarterTime) {
//        points = {
//                glm::vec3 {0.0f, 250.0f, radius},
//                glm::vec3 {radius * std::sin(M_PI / 6.0f), 250.0f, radius * std::sin(M_PI / 3.0f)},
//                glm::vec3 {radius * std::sin(M_PI / 3.0f), 250.0f, radius * std::sin(M_PI / 6.0f)},
//                glm::vec3 {radius, 250.0f, 0.0f}
//        };
//        eye = bezierPoint(points, ((float) age - (approachTime + 3 * quarterTime)) / quarterTime);
//    }
//    // nastavenie kamery pred bránu
//    else if (switchScene) {
//        eye.x = 220.0f;
//        eye.y = center.y = 10.0f;
//        eye.z = center.z = 15.0f;
//        switchScene = false;
//    }
//    // chôdza cez bránu
//    else if (age <= 30.0f) {
//        points = {
//                glm::vec3 {220.0f, 10.0f, 15.0f},
//                glm::vec3 {160.0f, 10.0f, 15.0f}
//        };
//        eye = bezierPoint(points, ((float) age - 25.0f) / 5.0f);
//        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
//    }
//    // pohľad vpravo
//    else if (age <= 32.0f) {
//        points = {
//                glm::vec3 {0.0f, 10.0f, 15.0f},
//                glm::vec3 {0.0f, 10.0f, -85.0f}
//        };
//        center = bezierPoint(points, ((float) age - 30.0f) / 2.0f);
//    }
//    // pohľad vľavo
//    else if (age <= 35.5f) {
//        points = {
//                glm::vec3 {0.0f, 10.0f, -85.0f},
//                glm::vec3 {0.0f, 10.0f, 85.0f}
//        };
//        center = bezierPoint(points, ((float) age - 32.0f) / 3.5f);
//    }
//    // pohyb šikmo vľavo
//    else if (age <= 40.0f) {
//        points = {
//                glm::vec3 {160.0f, 10.0f, 15.0f},
//                glm::vec3 {150.0f, 10.0f, 35.0f},
//                glm::vec3 {120.0f, 10.0f, 55.0f}
//        };
//        eye = bezierPoint(points, ((float) age - 35.5f) / 4.5f);
//        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
//        points = {
//                glm::vec3 {0.0f, 10.0f, 85.0f},
//                glm::vec3 {0.0f, 10.0f, 55.0f}
//        };
//        center = bezierPoint(points, ((float) age - 35.5f) / 4.5f);
//    }
//    // pohyb rovno
//    else if (age <= 45.0f) {
//        points = {
//                glm::vec3 {120.0f, 10.0f, 55.0f},
//                glm::vec3 {60.0f, 10.0f, 55.0f}
//        };
//        eye = bezierPoint(points, ((float) age - 40.0f) / 5.0f);
//        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
//    }
//    // pohybb šikmo vpravo
//    else if (age <= 50.0f) {
//        points = {
//                glm::vec3 {60.0f, 10.0f, 55.0f},
//                glm::vec3 {20.0f, 10.0f, 35.0f},
//                glm::vec3 {0.0f, 10.0f, 0.0f}
//        };
//        eye = bezierPoint(points, ((float) age - 45.0f) / 5.0f);
//        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
//        points = {
//                glm::vec3 {0.0f, 10.0f, 55.0f},
//                glm::vec3 {0.0f, 10.0f, -100.0f}
//        };
//        center = bezierPoint(points, ((float) age - 45.0f) / 5.0f);
//    }
//    else if (age <= 53.0f) {
//        points = {
//                glm::vec3{0.0f, 10.0f, 0.0f},
//                glm::vec3{0.0f, 10.0f, -36.0f}
//        };
//        eye = bezierPoint(points, ((float) age - 50.0f) / 3.0f);
//        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
//    }
//    // pohľad hore a späť
//    else if (age <= 60.0f) {
//        points = {
//                glm::vec3 {0.0f, 10.0f, -100.0f},
//                glm::vec3 {10.0f, 80.0f, -100.0f},
//                glm::vec3 {25.0f, 150.0f, -100.0f},
//                glm::vec3 {10.0f, 80.0f, -100.0f},
//                glm::vec3 {0.0f, 10.0f, -100.0f}
//        };
//        center = bezierPoint(points, ((float) age - 53.0f) / 7.0f);
//    }
    viewMatrix = lookAt(eye, center, glm::vec3(0.0, 1.0, 0.0));
}

//glm::vec3 Camera::cast(double u, double v) {
//    // Create point in Screen coordinates
//    glm::vec4 screenPosition{u, v, 0.0f, 1.0f};
//
//    // Use inverse matrices to get the point in world coordinates
//    auto invProjection = glm::inverse(projectionMatrix);
//    auto invView = glm::inverse(viewMatrix);
//
//    // Compute position on the camera plane
//    auto planePosition = invView * invProjection * screenPosition;
//    planePosition /= planePosition.w;
//
//    // Create direction vector
//    auto direction = glm::normalize(planePosition - glm::vec4{position, 1.0f});
//    return glm::vec3{direction};
//}

glm::vec3 Camera::bezierPoint(std::vector<glm::vec3> points, const float t) {
    for (int i = 0; i < points.size() - 1; i++) {
        for (int j = 0; j < points.size() - 1 - i; j++) {
            points[j] = glm::vec3{points[j].x + (points[j + 1].x - points[j].x) * t,
                                  points[j].y + (points[j + 1].y - points[j].y) * t,
                                  points[j].z + (points[j + 1].z - points[j].z) * t};
        }
    }
    return {points[0]};
}
