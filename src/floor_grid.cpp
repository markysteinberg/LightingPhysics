#include "floor_grid.h" 

FloorGrid::FloorGrid() : shader("assets/shaders/floor_grid.vert", "assets/shaders/floor_grid.frag") {}

void FloorGrid::setup() {
    float plane[] = {
        -100, 0, -100,
         100, 0, -100,
         100, 0,  100,
         100, 0,  100,
        -100, 0,  100,
        -100, 0, -100
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
}

void FloorGrid::draw(const glm::mat4& view, const glm::mat4& projection) {
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0f, -1.0f);

    shader.use();
    shader.setMat4("model", glm::mat4(1.0f));
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisable(GL_POLYGON_OFFSET_FILL);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void FloorGrid::enableShader(const glm::mat4& view, const glm::mat4 projection) const {
    shader.use();

    shader.setMat4("model", glm::mat4(1.0f));
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

GLuint FloorGrid::getVAO() const {
    return VAO;
}