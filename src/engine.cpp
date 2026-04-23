#include <iostream>
#include <stdexcept>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "engine.h" 
#include "config.h"

Engine::Engine() 
    : shader("assets/shaders/default.vert", "assets/shaders/default.frag"),
      object("assets/objects/sphere.obj") 
    {}
    
void Engine::init() {
    renderer.init();

    object.mesh.setup();
    std::cout << "setup done, VAO: " << object.mesh.VAO << '\n';
    object.scale = {1.0f, 1.0f, 1.0f};
    object.position = {0.0f, 0.0f, 0.0f};
    object.rotation = {0.0f, 0.0f, 0.0f};
}

int Engine::run(Window* window) {
    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window->get())) {
        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime; 

        window->processInput(&object);

        renderer.render(object, shader, dt);

        glfwSwapBuffers(window->get());
        glfwPollEvents();
    }

    return 0;
}