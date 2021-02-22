//  DrawKit
//  Created by David Spry on 2/2/21.

#include "Shader.hpp"

namespace DrawKit {

Shader::~Shader()
{
    glDeleteProgram(rendererID);
}

// MARK: - PUBLIC INTERFACE

void Shader::use() const
{
    glUseProgram(rendererID);
}

uint32_t Shader::getRendererID() const
{
    return rendererID;
}

Shader * Shader::create(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
    Shader * shader = new Shader();
    shader->createFromFiles(vertexShaderPath, fragmentShaderPath);
    return shader;
}

Shader * Shader::create(const std::string & vertexShaderPath,
                        const std::string & geometryShaderPath,
                        const std::string & fragmentShaderPath)
{
    Shader * shader = new Shader();
    shader->createFromFiles(vertexShaderPath, fragmentShaderPath, geometryShaderPath);
    return shader;
}

void Shader::destroy()
{
    glDeleteProgram(rendererID);
}

// MARK: - UNIFORMS

void Shader::setUniform(std::string_view handle, bool value)
{
    glUniform1i(glGetUniformLocation(rendererID, handle.data()), static_cast<int>(value));
}

void Shader::setUniform(std::string_view handle, int value)
{
    glUniform1i(glGetUniformLocation(rendererID, handle.data()), value);
}

void Shader::setUniform(std::string_view handle, float value)
{
    glUniform1f(glGetUniformLocation(rendererID, handle.data()), value);
}

void Shader::setUniform(std::string_view handle, const DrawKit::RGBA & value)
{
    glUniform4fv(glGetUniformLocation(rendererID, handle.data()), 1, &(value.r));
}

void Shader::setUniform(std::string_view handle, const glm::vec2 & value)
{
    glUniform2fv(glGetUniformLocation(rendererID, handle.data()), 1, &(value[0]));
}

void Shader::setUniform(std::string_view handle, const glm::mat4 & value)
{
    glUniformMatrix4fv(glGetUniformLocation(rendererID, handle.data()), 1, GL_FALSE, glm::value_ptr(value));
}

// MARK: - SHADER CREATION

static std::string readFile(const std::string & filepath)
{
    std::ifstream file (filepath);
    return std::string ((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
}

uint32_t Shader::compileShader(GLenum type, const std::string & shaderSource)
{
    GLuint const   shader = glCreateShader(type);
    GLchar const * source = shaderSource.c_str();

    glShaderSource (shader, 1, &source, 0);
    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE)
    {
        glDeleteShader(shader);
        DK_FATAL_ERROR("Shader", "Shader failed to compile.");
    }
    
    return shader;
}

void Shader::linkProgram(const uint32_t & program, const std::vector<GLuint> & shaders)
{
    for (auto & shader : shaders)
        glAttachShader(program, shader);
    
    glLinkProgram(program);
    
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

    if (isLinked == GL_FALSE)
    {
        for (auto & shader : shaders)
            glDeleteShader(shader);
        
        glDeleteProgram(program);
        DK_FATAL_ERROR(__FILE_NAME__, "Program failed to link.");
    }
    
    for (auto & shader : shaders)
    {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }

    rendererID = program;
}

void Shader::createFromFiles(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
    std::vector<GLuint> shaders;

    std::string vshader = readFile(vertexShaderPath);
    std::string fshader = readFile(fragmentShaderPath);

    shaders.emplace_back(compileShader(GL_VERTEX_SHADER,   vshader));
    shaders.emplace_back(compileShader(GL_FRAGMENT_SHADER, fshader));
    
    uint32_t program = glCreateProgram();
    
    linkProgram(program, shaders);
}

void Shader::createFromFiles(const std::string & vertexShaderPath,
                             const std::string & geometryShaderPath,
                             const std::string & fragmentShaderPath)
{
    std::vector<GLuint> shaders;

    std::string vshader = readFile(vertexShaderPath);
    std::string fshader = readFile(fragmentShaderPath);
    std::string gshader = readFile(geometryShaderPath);

    shaders.emplace_back(compileShader(GL_VERTEX_SHADER,   vshader));
    shaders.emplace_back(compileShader(GL_GEOMETRY_SHADER, gshader));
    shaders.emplace_back(compileShader(GL_FRAGMENT_SHADER, fshader));
    
    uint32_t program = glCreateProgram();
    
    linkProgram(program, shaders);
}

}
