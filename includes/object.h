#ifndef OBJECT_H
#define OBJECT_H

#include <string> 

#include "mesh.h" 
#include "shader.h" 

#include <glm/vec3.hpp>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

class Object {
public:
    Mesh mesh;
    
    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};
    glm::vec3 scale{1.0f};
    
    bool rotationMode = false; 

    Object(const std::string& path);
    Object() = default;

    glm::mat4 getModel() const;

    void draw(const Shader& shader) const;
private:

};

#endif