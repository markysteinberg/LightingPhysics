#include "camera.h" 
#include "util.h"

glm::mat4 Camera::getView() const {
    return glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}
    
glm::mat4 Camera::getProjection() const { 
    return glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
}

void Camera::processInput(GLFWwindow* window, float dt) {
    if (is_key_pressed_once(window, GLFW_KEY_F1)) {  
        this->pursueMode = !this->pursueMode;
    }
    if (pursueMode) { 
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            distance -= 5.0f * dt;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {  
            distance += 5.0f * dt;
        }
        distance = glm::clamp(distance, minDistance, maxDistance);
    } else {
        glm::vec3 forward = glm::normalize(target - position);
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            position += forward * 5.0f * dt;
            target   += forward * 5.0f * dt;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            position -= forward * 5.0f * dt;
            target   -= forward * 5.0f * dt;
        }
    }
}

void Camera::follow(const glm::vec3& targetPos, const glm::vec3& forward, float dt) {
    glm::vec3 behind = glm::normalize(forward);

    float height = 2.0f;
    float dynamicHeight = height + distance * 0.3f;
    glm::vec3 desiredPos = targetPos + behind * distance + glm::vec3(0.0f, dynamicHeight, 0.0f);;

    float smooth = 5.0f;
    position += (desiredPos - position) * smooth * dt;
    target = targetPos;
}