#include "util.h" 

namespace Util { 
    bool is_key_pressed_once(GLFWwindow* window, int key) {
        static bool last[GLFW_KEY_LAST + 1] = { false };

        bool now = glfwGetKey(window, key) == GLFW_PRESS; 

        bool pressed = now && !last[key];
        last[key] = now;

        return pressed; 
    }
}