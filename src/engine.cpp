#include <iostream>
#include <stdexcept>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "engine.h" 
#include "config.h"

Engine::Engine() 
    : shader("assets/shaders/default.vert", "assets/shaders/default.frag"),
      shape("assets/objects/cube.obj")
    {}
    
void Engine::init() {
    renderer.init();

    floorGrid.setup();

    shape.mesh.setup();
    shape.scale = {0.60f, 0.60f, 0.60f};
    shape.position = {0.0f, 0.0f, 0.0f};
    shape.rotation = {0.0f, 0.0f, 0.0f};
}

void Engine::update(float dt) {
    if (shape.rotationMode) {
        shape.rotation.y += 2.0f * dt;
    }
}

int Engine::run(Window* window) {
    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window->get())) {
        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime; 

        window->processInput(&shape);

        glm::mat4 view = camera.getView();
        glm::mat4 projection = camera.getProjection();

        update(dt);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.renderFloorGrid(floorGrid, view, projection);
        renderer.renderObject(shape, shader, camera.position, view, projection);

        glfwSwapBuffers(window->get());
        glfwPollEvents();
    }

    return 0;
}
