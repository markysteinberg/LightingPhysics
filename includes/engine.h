#ifndef ENGINE_H
#define ENGINE_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <utility> 

#include "renderer.h"
#include "window.h"
#include "object.h"
#include "shader.h" 

class Engine {
public: 
    Engine();
    void init();
    int run(Window* window);
private:
    Shader shader;
    Renderer renderer;
    Object object;
};

#endif