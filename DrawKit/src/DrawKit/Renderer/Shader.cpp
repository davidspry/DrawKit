//  DrawKit
//  Created by David Spry on 2/2/21.

#include "Shader.hpp"

namespace DrawKit {

Shader::~Shader()
{
    glDeleteProgram(rendererID);
}

uint32_t Shader::getRendererID()
{
    return rendererID;
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

Shader * Shader::create(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
    Shader * shader = new Shader();
    shader->createFromFiles(vertexShaderPath, fragmentShaderPath);
    return shader;
}

static std::string readFile(const std::string & filepath)
{
    std::ifstream file (filepath);
    return std::string ((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
}

void Shader::createFromFiles(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
    std::string vshader = readFile(vertexShaderPath);
    std::string fshader = readFile(fragmentShaderPath);
    uint32_t program    = glCreateProgram();

    GLuint vertexShader   = compileShader(GL_VERTEX_SHADER,   vshader);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fshader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    
    if (isLinked == GL_FALSE)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(program);
        
        DK_FATAL_ERROR("Shader", "Program failed to link.");
    }
    
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    rendererID = program;
}

}
