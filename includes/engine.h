#ifndef ENGINE_H
#define ENGINE_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <utility> 

#include "renderer.h"
#include "window.h"
#include "object.h"
#include "shader.h" 
#include "floor_grid.h"
#include "camera.h"

class Engine {
public: 
    Engine();
    void init();
    int run(Window* window);
private:
    void update(float dt);

    Shader shader;
    Renderer renderer;
    Camera camera;
    FloorGrid floorGrid;    
    Object shape;
};

#endif
