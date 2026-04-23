#ifndef GRID_H
#define GRID_H

#include "glad/glad.h"

#include <glm/glm.hpp>

#include "shader.h" 

class FloorGrid {
public: 
    FloorGrid();

    void draw(const glm::mat4& view, const glm::mat4& projection);
    void setup();

    void enableShader(const glm::mat4& view, const glm::mat4 projection) const;

    GLuint getVAO() const;
    bool on = true;

private: 
    GLuint VBO, VAO;
    Shader shader;
};



#endif 