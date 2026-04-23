#include "glad/glad.h"

#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <iostream>
#include <cstdint>

#include <assimp/postprocess.h>

#include "mesh.h" 

using u32 = uint32_t;

Mesh::Mesh(const std::string& path) {
    Assimp::Importer importer; 

    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_GenNormals);

    if (!scene || !scene->mRootNode) {
        std::cerr << "Failed to load: " << path << " " << importer.GetErrorString() << '\n';
        return ;
    }

    for (u32 k = 0; k < scene->mNumMeshes; k++) {
        aiMesh* m = scene->mMeshes[k];
        
        //u32 baseIndex = this->vertices.size();

        // Vertices
        for (u32 i = 0; i < m->mNumVertices; i++) {
            Vertex v{};
            v.position = glm::vec3(m->mVertices[i].x, m->mVertices[i].y, m->mVertices[i].z);

            if (m->HasNormals()) {
                v.normal = glm::vec3(m->mNormals[i].x, m->mNormals[i].y, m->mNormals[i].z); 
            } else {
                v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
            }

            this->vertices.push_back(v);
        }

        // Faces  
        for (u32 i = 0; i < m->mNumFaces; i++) {
            aiFace face = m->mFaces[i];
            for (u32 j = 0; j < face.mNumIndices; j++) {
                this->indices.push_back(face.mIndices[j]);
            }
        }     
    }
}

Mesh::~Mesh() {
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (EBO) glDeleteBuffers(1, &EBO);
}

void Mesh::setup() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}