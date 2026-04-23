#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include "object.h"

class Renderer {
public:
    static void init();
    static void render(Object& object, Shader& shader, float dt);
};

#endif