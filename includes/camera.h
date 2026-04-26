#ifndef CAMERA_H
#define CAMERA_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "config.h"

class Camera {
public: 
    glm::vec3 position{1.5f, 1.5f, 1.5f};
    glm::vec3 target{0.0f, 0.0f, 0.0f};

    glm::mat4 getView() const;
    glm::mat4 getProjection() const;

    void processInput(GLFWwindow* window, float dt);

    bool pursueMode = false;
    void follow(const glm::vec3& targetPos, const glm::vec3& forward, float dt);

    float distance = 5.0f;     
    float minDistance = 2.0f;
    float maxDistance = 15.0f;

    glm::vec3 offsetDir = glm::vec3(0.0f, 0.3f, 1.0f); 
};

#endif 