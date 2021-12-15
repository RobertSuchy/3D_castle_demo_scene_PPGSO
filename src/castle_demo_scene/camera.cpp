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
    if (age <= approachTime) {
        points = {
                glm::vec3 {radius + 3000.0f, 1000.0f, 0.0f},
                glm::vec3 {radius + 2000.0f, 600.0f, 0.0f},
                glm::vec3 {radius + 1000.0f, 400.0f, 0.0f},
                glm::vec3 {radius, 250.0f, 0.0f}
        };
        eye = bezierPoint(points, ((float) age) / approachTime);
    }
    // rotácia okolo hradu 1/4
    else if (age <= approachTime + quarterTime) {
        points = {
                glm::vec3 {radius, 250.0f, 0.0f},
                glm::vec3 {radius * std::sin(M_PI / 3.0f), 250.0f, -radius * std::sin(M_PI / 6.0f)},
                glm::vec3 {radius * std::sin(M_PI / 6.0f), 250.0f, -radius * std::sin(M_PI / 3.0f)},
                glm::vec3 {0.0f, 250.0f, -radius}
        };
        eye = bezierPoint(points, ((float) age - approachTime) / quarterTime);
    }
    // rotácia okolo hradu 2/4
    else if (age <= approachTime + 2 * quarterTime) {
        points = {
                glm::vec3 {0.0f, 250.0f, -radius},
                glm::vec3 {-radius * std::sin(M_PI / 6.0f), 250.0f, -radius * std::sin(M_PI / 3.0f)},
                glm::vec3 {-radius * std::sin(M_PI / 3.0f), 250.0f, -radius * std::sin(M_PI / 6.0f)},
                glm::vec3 {-radius, 250.0f, 0.0f}
        };
        eye = bezierPoint(points, ((float) age - (approachTime + quarterTime)) / quarterTime);
    }
    // rotácia okolo hradu 3/4
    else if (age <= approachTime + 3 * quarterTime) {
        points = {
                glm::vec3 {-radius, 250.0f, 0.0f},
                glm::vec3 {-radius * std::sin(M_PI / 3.0f), 250.0f, radius * std::sin(M_PI / 6.0f)},
                glm::vec3 {-radius * std::sin(M_PI / 6.0f), 250.0f, radius * std::sin(M_PI / 3.0f)},
                glm::vec3 {0.0f, 250.0f, radius}
        };
        eye = bezierPoint(points, ((float) age - (approachTime + 2 * quarterTime)) / quarterTime);
    }
    // rotácia okolo hradu 4/4
    else if (age <= approachTime + 4 * quarterTime) {
        points = {
                glm::vec3 {0.0f, 250.0f, radius},
                glm::vec3 {radius * std::sin(M_PI / 6.0f), 250.0f, radius * std::sin(M_PI / 3.0f)},
                glm::vec3 {radius * std::sin(M_PI / 3.0f), 250.0f, radius * std::sin(M_PI / 6.0f)},
                glm::vec3 {radius, 250.0f, 0.0f}
        };
        eye = bezierPoint(points, ((float) age - (approachTime + 3 * quarterTime)) / quarterTime);
    }
    // nastavenie kamery pred bránu
    else if (switchScene) {
        eye.x = 220.0f;
        eye.y = center.y = 10.0f;
        eye.z = center.z = 15.0f;
        switchScene = false;
    }
    // chôdza cez bránu
    else if (age <= 30.0f) {
        points = {
                glm::vec3 {220.0f, 10.0f, 15.0f},
                glm::vec3 {160.0f, 10.0f, 15.0f}
        };
        eye = bezierPoint(points, ((float) age - 25.0f) / 5.0f);
        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
    }
    // pohľad vpravo
    else if (age <= 32.0f) {
        points = {
                glm::vec3 {0.0f, 10.0f, 15.0f},
                glm::vec3 {0.0f, 10.0f, -85.0f}
        };
        center = bezierPoint(points, ((float) age - 30.0f) / 2.0f);
    }
    // pohľad vľavo
    else if (age <= 35.5f) {
        points = {
                glm::vec3 {0.0f, 10.0f, -85.0f},
                glm::vec3 {0.0f, 10.0f, 85.0f}
        };
        center = bezierPoint(points, ((float) age - 32.0f) / 3.5f);
    }
    // pohyb šikmo vľavo
    else if (age <= 40.0f) {
        points = {
                glm::vec3 {160.0f, 10.0f, 15.0f},
                glm::vec3 {150.0f, 10.0f, 35.0f},
                glm::vec3 {120.0f, 10.0f, 55.0f}
        };
        eye = bezierPoint(points, ((float) age - 35.5f) / 4.5f);
        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
        points = {
                glm::vec3 {0.0f, 10.0f, 85.0f},
                glm::vec3 {0.0f, 10.0f, 55.0f}
        };
        center = bezierPoint(points, ((float) age - 35.5f) / 4.5f);
    }
    // pohyb rovno
    else if (age <= 45.0f) {
        points = {
                glm::vec3 {120.0f, 10.0f, 55.0f},
                glm::vec3 {60.0f, 10.0f, 55.0f}
        };
        eye = bezierPoint(points, ((float) age - 40.0f) / 5.0f);
        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
    }
    // pohybb šikmo vpravo
    else if (age <= 50.0f) {
        points = {
                glm::vec3 {60.0f, 10.0f, 55.0f},
                glm::vec3 {20.0f, 10.0f, 35.0f},
                glm::vec3 {0.0f, 10.0f, 0.0f}
        };
        eye = bezierPoint(points, ((float) age - 45.0f) / 5.0f);
        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
        points = {
                glm::vec3 {0.0f, 10.0f, 55.0f},
                glm::vec3 {0.0f, 10.0f, -100.0f}
        };
        center = bezierPoint(points, ((float) age - 45.0f) / 5.0f);
    }
    else if (age <= 53.0f) {
        points = {
                glm::vec3{0.0f, 10.0f, 0.0f},
                glm::vec3{0.0f, 10.0f, -36.0f}
        };
        eye = bezierPoint(points, ((float) age - 50.0f) / 3.0f);
        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
    }
    // pohľad hore na dym a späť
    else if (age <= 60.0f) {
        points = {
                glm::vec3 {0.0f, 10.0f, -100.0f},
                glm::vec3 {10.0f, 80.0f, -100.0f},
                glm::vec3 {25.0f, 150.0f, -100.0f},
                glm::vec3 {10.0f, 80.0f, -100.0f},
                glm::vec3 {0.0f, 10.0f, -100.0f}
        };
        center = bezierPoint(points, ((float) age - 53.0f) / 7.0f);
    }
    // pohľad vľavo na hodiny
    else if (age <= 63.0f) {
        points = {
                glm::vec3{0.0f, 10.0f, -100.0f},
                glm::vec3{-98.5f, 27.75f, -39.75f}
        };
        center = bezierPoint(points, ((float) age - 60.0f) / 3.0f);
    }
    // pohyb rovno k hodinám
    else if (age <= 68.0f) {
        points = {
                glm::vec3{0.0f, 10.0f, -36.0f},
                glm::vec3{-60.0f, 10.0f, -36.0f}
        };
        eye = bezierPoint(points, ((float) age - 63.0f) / 5.0f);
        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
    }
    // pohľad vpravo na schody
    else if (age <= 72.0f) {
        points = {
                glm::vec3{-98.5f, 27.75f, -39.75f},
                glm::vec3{-125.0f, 10.0f, -140.0f}
        };
        center = bezierPoint(points, ((float) age - 68.0f) / 4.0f);
    }
    // pohyb šikmo vpravo ku schodom
    else if (age <= 80.0f) {
        points = {
                glm::vec3{-60.0f, 10.0f, -36.0f},
                glm::vec3{-85.0f, 10.0f, -60.0f},
                glm::vec3{-90.0f, 10.0f, -140.0f}
        };
        eye = bezierPoint(points, ((float) age - 72.0f) / 8.0f);
        eye.y = std::sin(age * 10.0f) * 0.25f + 10.0f;
    }
    // pohyb hore po schodoch
    else if (age <= 85.0f) {
        points = {
                glm::vec3{-90.0f, 10.0f, -140.0f},
                glm::vec3{-160.0f, 50.0f, -140.0f}
        };
        eye = bezierPoint(points, ((float) age - 80.0f) / 5.0f);
        eye.y = std::sin(age * 10.0f) * 0.5f + eye.y;
        points = {
                glm::vec3{-125.0f, 10.0f, -140.0f},
                glm::vec3{-200.0f, 50.0f, -140.0f}
        };
        center = bezierPoint(points, ((float) age - 80.0f) / 5.0f);
    }
    // pohyb po hradbách
    else if (age <= 100.0f) {
        points = {
                glm::vec3{-160.0f, 50.0f, -140.0f},
                glm::vec3{-160.0f, 50.0f, 100.0f}
        };
        eye = bezierPoint(points, ((float) age - 85.0f) / 15.0f);
        eye.y = std::sin(age * 10.0f) * 0.25f + eye.y;
        points = {
                glm::vec3{-200.0f, 50.0f, -140.0f},
                glm::vec3{-100.0f, 50.0f, 200.0f}
        };
        center = bezierPoint(points, ((float) age - 85.0f) / 15.0f);
    }
    else if (age <= 105.0f) {
        points = {
                glm::vec3{-160.0f, 50.0f, 100.0f},
                glm::vec3{-100.0f, 50.0f, 100.0f}
        };
        eye = bezierPoint(points, ((float) age - 100.0f) / 5.0f);
        eye.y = std::sin(age * 10.0f) * 0.25f + eye.y;
        points = {
                glm::vec3{-100.0f, 50.0f, 200.0f},
                glm::vec3{0.0f, 50.0f, 200.0f}
        };
        center = bezierPoint(points, ((float) age - 100.0f) / 5.0f);
    }
    // pozorovanie oštepu po trajektórii
    else if (age <= 108.0f) {
        eye.x = -55.0f;
        eye.y = 500.0f * (age - 105.0f) * std::sin(M_PI / 8) - 9.81 * 9 * pow((age - 105.0f), 2) / 2 + 10;
        eye.z = 1975.0f - 500.0f * (age - 105.0f) * std::cos(M_PI / 8) + 20;
        center.x = -55.0f;
        center.y = 0.0;
        center.z = 0.0;

    }
    // pozorovanie oštepu z hradieb
    else if (age <= 109.0f) {
        eye = glm::vec3{-100.0f, 50.0f, 100.0f};
        points = {
                glm::vec3{0.0f, 50.0f, 200.0f},
                glm::vec3{0.0f, 50.0f, 250.0f},
                glm::vec3{0.0f, 50.0f, 200.0f}
        };
        center = bezierPoint(points, ((float) age - 108.0f) / 1.0f);
    }
    else if (age <= 115.0f) {
        points = {
                glm::vec3{0.0f, 50.0f, 200.0f},
                glm::vec3{-100.0f, 60.0f, 400.0f}
        };
        center = bezierPoint(points, ((float) age - 109.0f) / 6.0f);
    }
    // zásah oštepom a pád
    else if (age <= 117.0f) {
        points = {
                glm::vec3{-160.0f, 50.0f, 100.0f},
                glm::vec3{-100.0f, 0.0f, 80.0f}
        };
        eye = bezierPoint(points, ((float) age - 115.0f) / 2.0f);
        points = {
                glm::vec3{-100.0f, 60.0f, 400.0f},
                glm::vec3{-100.0f, 100.0f, 100.0f}
        };
        center = bezierPoint(points, ((float) age - 115.0f) / 2.0f);
    }
    // finálny pohľad na vlajku a časť hradu
    else if (age > 119.0f) {
        eye.x = -38;
        eye.y = 106;
        eye.z = 250;
        center.x = -38;
        center.y = 106;
        center.z = 105;
    }
    viewMatrix = lookAt(eye, center, glm::vec3(0.0, 1.0, 0.0));
}

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
