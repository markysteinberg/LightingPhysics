#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glad/glad.h"

#include <glm/glm.hpp>

std::string readGLSL(const char* path);

class Shader {
private:
    GLuint ID = 0;
public:
    Shader(const char* vspath, const char* fspath);
    Shader() = default;    
    ~Shader();
    
    void use() const;

    GLuint getID() const;

    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& v) const;
private:
    void check_compile(GLuint shader);
    void check_link(GLuint program);
};

#endif