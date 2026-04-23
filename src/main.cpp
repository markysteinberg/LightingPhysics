#include <stdexcept> 

#include "engine.h" 
#include "config.h" 

#include "glad/glad.h" 

int main(int argc, char* argv[]) {
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("GLAD INIT FAILED");;
    }        
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    int exitStatus = 0;
    {
        Engine engine;
        engine.init();

        exitStatus = engine.run(&window);
    }
    glfwTerminate();

    return exitStatus;
}