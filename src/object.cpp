#include "object.h" 

Object::Object(const std::string& path) : mesh(path) {}

glm::mat4 Object::getModel() const {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);

    model = glm::rotate(model, rotation.x, glm::vec3(1,0,0));
    model = glm::rotate(model, rotation.y, glm::vec3(0,1,0));
    model = glm::rotate(model, rotation.z, glm::vec3(0,0,1));

    model = glm::scale(model, scale);

    return model;
}

void Object::draw(const Shader& shader) const {
    glm::mat4 model = getModel();

    shader.setMat4("model", model); 

    mesh.draw();
}