#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include <glm/glm.hpp>

#include "object.h"
#include "floor_grid.h" 

class Renderer {
public:
    static void init();
    static void renderObject(Object& object, Shader& shader, const glm::vec3 cameraPos, const glm::mat4 view, const glm::mat4 projection);
    static void renderFloorGrid(FloorGrid& grid, const glm::mat4 view, const glm::mat4 projection);
};

#endif