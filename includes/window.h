#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "object.h" 

void frambuffer_size_callback(GLFWwindow* window, int width, int height);

bool is_key_pressed_once(GLFWwindow* window, int key);

class Window {
public:
    Window(int w, int h, const char* title);    
    ~Window();

    void processInput(Object* object);

    GLFWwindow* get() const;
private: 
    GLFWwindow* window = nullptr;
};

#endif