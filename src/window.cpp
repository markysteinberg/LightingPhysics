#include <stdexcept>

#include <glm/vec3.hpp>

#include "glad/glad.h"

#include "window.h"

void frambuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool is_key_pressed_once(GLFWwindow* window, int key) {
    static bool last[GLFW_KEY_LAST + 1] = { false };

    bool now = glfwGetKey(window, key) == GLFW_PRESS; 

    bool pressed = now && !last[key];
    last[key] = now;

    return pressed; 
}

Window::Window(int w, int h, const char* title) {
    if (!glfwInit()) {
        throw std::runtime_error("GLFW INIT FAILED");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (!window) {
        throw std::runtime_error("FAILED TO CREATE GLFLW WINDOW");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, frambuffer_size_callback);
}

Window::~Window() {
    if (window) glfwDestroyWindow(window);
}

void Window::processInput(Object* object) {
    if (is_key_pressed_once(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    }
    if (is_key_pressed_once(window, GLFW_KEY_UP)) {
        if (object->scale.x < 1.5f) {
            object->scale += glm::vec3(0.1f);
        }
    }
    if (is_key_pressed_once(window, GLFW_KEY_DOWN)) {
        if (object->scale.x > 0.1f) {
            object->scale -= glm::vec3(0.1f);
        }
    }
    if (is_key_pressed_once(window, GLFW_KEY_RIGHT)) {
        if (!object->rotationMode)
            object->rotation.y += 0.25f;
    }
    if (is_key_pressed_once(window, GLFW_KEY_LEFT)) {
        if (!object->rotationMode)
            object->rotation.y -= 0.25f;
    }
    if (is_key_pressed_once(window, GLFW_KEY_R)) {
        object->rotationMode = !object->rotationMode;
    }
}

GLFWwindow* Window::get() const { return window; } 







