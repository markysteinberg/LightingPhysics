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
#include "camera.h" 

void Renderer::init() {
    glEnable(GL_DEPTH_TEST);
}

void Renderer::renderObject(Object& object, Shader& shader, const glm::vec3 cameraPos, const glm::mat4 view, const glm::mat4 projection) {
    shader.use();

    glm::mat4 model = object.getModel();

    glm::mat4 mvp = projection * view * model;

    shader.setMat4("mvp", mvp); 
    shader.setVec3("lightPos", glm::vec3(1.0f, 4.0f, 2.0f)); 
    shader.setVec3("viewPos", cameraPos);
    object.draw(shader); 
}

void Renderer::renderFloorGrid(FloorGrid& grid, const glm::mat4 view, const glm::mat4 projection) {
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0f, -1.0f);

    grid.enableShader(view, projection);

    glBindVertexArray(grid.getVAO());
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisable(GL_POLYGON_OFFSET_FILL);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}