//  DrawKit
//  Created by David Spry on 2/2/21.

#ifndef SHADER_HPP
#define SHADER_HPP

#include "dk.pch"

namespace DrawKit
{

class Shader
{
public:
    ~Shader();
 
private:
    Shader() = default;
    
public:
    uint32_t getRendererID();
    
    static Shader * create(const std::string & vertexShaderPath, const std::string & fragmentShaderPath);
    
private:
    uint32_t compileShader(GLenum type, const std::string & source);

    void createFromFiles(const std::string & vertexShaderPath, const std::string & fragmentShaderPath);

private:
    uint32_t rendererID;
};

}

#endif
