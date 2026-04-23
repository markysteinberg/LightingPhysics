#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string> 

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using GLuint = unsigned int;

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
};

class Mesh {
public:
    Mesh(const std::string& path);
    Mesh() = default;
    ~Mesh();    

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    
    GLuint VBO = 0, VAO = 0, EBO = 0;
    
    void setup();

    void draw() const;
};

#endif 