#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "config.h"

class Camera {
public: 
    glm::vec3 position{1.5f, 1.5f, 1.5f};
    
    glm::mat4 getView() const;
    glm::mat4 getProjection() const;
};

#endif 