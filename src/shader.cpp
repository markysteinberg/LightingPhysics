#include <string> 
#include <stdexcept>
#include <fstream>
#include <sstream> 
#include <iostream>

#include "shader.h" 

std::string readGLSL(const char* path) {
    std::ifstream file(path);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

Shader::Shader(const char* vspath, const char* fspath) {
    std::string vss = readGLSL(vspath);
    std::string fss = readGLSL(fspath);
    std::cout << "VS length: " << vss.size() << " FS length: " << fss.size() << '\n';

    if (vss.empty() || fss.empty()) {
        throw std::runtime_error("GLSL SHADER FILE FAILED TO LOAD"); 
    }

    const char* vertex_shader_source = vss.c_str();
    const char* fragment_shader_source = fss.c_str();

    GLuint vs_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs_id, 1, &vertex_shader_source, nullptr);
    glCompileShader(vs_id);
    check_compile(vs_id);
 
    GLuint fs_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs_id, 1, &fragment_shader_source, nullptr);
    glCompileShader(fs_id);
    check_compile(fs_id);

    ID = glCreateProgram();
    glAttachShader(ID, vs_id);
    glAttachShader(ID, fs_id);
    glLinkProgram(ID);
    check_link(ID);

    glDeleteShader(vs_id);
    glDeleteShader(fs_id);
}

void Shader::use() const { glUseProgram(ID); }

GLuint Shader::getID() const { return ID; }

Shader::~Shader() {
    if (ID) glDeleteProgram(ID);
}

void Shader::check_compile(GLuint shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        throw std::runtime_error(infoLog);
    }
}

void Shader::check_link(GLuint program) {
    int success;
    char infoLog[512]; 
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        throw std::runtime_error(infoLog);
    }
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    int loc = glGetUniformLocation(ID, name.c_str());
    std::cout << name << " loc: " << loc << '\n';
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& v) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), v.x, v.y, v.z);
}