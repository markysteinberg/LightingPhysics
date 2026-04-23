#include "camera.h" 

glm::mat4 Camera::getView() const {
    return glm::lookAt(position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
    
glm::mat4 Camera::getProjection() const { 
    return glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);
}