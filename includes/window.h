#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "object.h" 
#include "floor_grid.h"

void frambuffer_size_callback(GLFWwindow* window, int width, int height);

class Window {
public:
    Window(int w, int h, const char* title);    
    ~Window();

    void processInput(Object* object, FloorGrid* grid);

    GLFWwindow* get() const;
private: 
    GLFWwindow* window = nullptr;
};

#endif