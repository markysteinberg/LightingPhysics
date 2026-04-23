#include <iostream> 

#include "glad/glad.h" 

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.h" 
#include "object.h" 
#include "config.h" 

void Renderer::init() {
    glEnable(GL_DEPTH_TEST);
}

void Renderer::render(Object& object, Shader& shader, float dt) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    glm::vec3 cameraPos = glm::vec3(1.5f, 1.5f, 1.5f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view = glm::lookAt(cameraPos, target, up);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

    if (object.rotationMode) {
        object.rotation.y += 2.0f * dt;
    }

    glm::mat4 model = object.getModel();

    glm::mat4 mvp = projection * view * model;
    
    std::cout << "shader ID: " << shader.getID() << '\n';
    shader.setMat4("mvp", mvp); std::cout << "mvp: " << glGetError() << '\n';
    shader.setVec3("lightPos", glm::vec3(1.0f, 1.0f, 2.0f)); std::cout << "lightPos: " << glGetError() << '\n';
    shader.setVec3("viewPos", cameraPos); std::cout << "viewPos: " << glGetError() << '\n';
    object.draw(shader); std::cout << "draw: " << glGetError() << '\n';   

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) std::cout << "GL ERROR: " << err << '\n';
}