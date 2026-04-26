#include <iostream>
#include <stdexcept>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "engine.h" 
#include "config.h"

Engine::Engine() 
    : shader("assets/shaders/default.vert", "assets/shaders/default.frag"),
      shape("assets/objects/sphere.obj")
    {}
    
void Engine::init() {
    renderer.init();

    floorGrid.setup();

    shape.mesh.setup();
    shape.scale = {0.60f, 0.60f, 0.60f};
    shape.position = {0.0f, 0.0f, 0.0f};
    shape.rotation = {0.0f, 0.0f, 0.0f};
    shape.hasRigidBody = true;
    shape.rigidbody.useGravity = true;
    shape.rigidbody.mass = 1.0f; 
}

void Engine::handleGameInput(GLFWwindow* window) {
    if (shape.hasRigidBody) {     
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            shape.rigidbody.velocity.y = 2.5f;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            shape.rigidbody.applyForce({0.0f, 0.0f, -10.0f});
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            shape.rigidbody.applyForce({-10.0f, 0.0f, 0.0f});
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            shape.rigidbody.applyForce({0.0f, 0.0f, 10.0f});
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            shape.rigidbody.applyForce({10.0f, 0.0f, 0.0f});
        }
    }
}

void Engine::update(float dt) {
    if (shape.rotationMode) {
        shape.rotation.y += 2.0f * dt;
    }
    if (shape.hasRigidBody) {
        shape.rigidbody.integrate(shape.position, dt);
    }
    glm::vec3 forward;
    forward.x = sin(shape.rotation.y);
    forward.z = cos(shape.rotation.y);
    forward.y = 0.0f;
    forward = glm::normalize(forward);
    if (camera.pursueMode) {
        camera.follow(shape.position, forward, dt);
    }
}

int Engine::run(Window* window) {
    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window->get())) {
        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime; 

        window->processInput(&shape, &floorGrid);
        camera.processInput(window->get(), dt);
        handleGameInput(window->get());

        glm::mat4 view = camera.getView();
        glm::mat4 projection = camera.getProjection();

        update(dt);

        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (floorGrid.on) renderer.renderFloorGrid(floorGrid, view, projection);
        renderer.renderObject(shape, shader, camera.position, view, projection);

        glfwSwapBuffers(window->get());
        glfwPollEvents();
    }

    return 0;
}
