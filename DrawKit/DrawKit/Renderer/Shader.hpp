//  DrawKit
//  Created by David Spry on 2/2/21.

#ifndef SHADER_HPP
#define SHADER_HPP

#include "dk.pch"

namespace DrawKit
{

/// @brief A GLSL shader program.

class Shader
{
private:
     Shader() = default;
    
public:
    ~Shader();

// MARK: - PUBLIC INTERFACE

public:
    /// @brief Create a new shader program from the given GLSL source files.
    /// @param vertexShaderPath The filepath of the desired vertex shader source file.
    /// @param fragmentShaderPath The filepath of the desired fragment shader source file.

    static Shader * create(const std::string & vertexShaderPath,
                           const std::string & fragmentShaderPath);
    
    /// @brief Create a new shader program from the given GLSL source files.
    /// @param vertexShaderPath The filepath of the desired vertex shader source file.
    /// @param geometryShaderPath The filepath of the desired geometry shader source file.
    /// @param fragmentShaderPath The filepath of the desired fragment shader source file.

    static Shader * create(const std::string & vertexShaderPath,
                           const std::string & geometryShaderPath,
                           const std::string & fragmentShaderPath);
    
    /// @brief Delete and destroy the shader program.

    void destroy();

public:
    /// @brief Enable the shader program for use.

    void use() const;
    
    /// @brief Get the shader program's ID.
    
    uint32_t getRendererID() const;
    
// MARK: - UNIFORMS

    /// @brief Set the value of the given uniform.
    /// @param handle The uniform's name.
    /// @param value The desired value.

    void setUniform(std::string_view handle, bool  value);
    
    /// @brief Set the value of the given uniform.
    /// @param handle The uniform's name.
    /// @param value The desired value.
    
    void setUniform(std::string_view handle, int   value);
    
    /// @brief Set the value of the given uniform.
    /// @param handle The uniform's name.
    /// @param value The desired value.
    
    void setUniform(std::string_view handle, float value);
    
    /// @brief Set the value of the given uniform.
    /// @param handle The uniform's name.
    /// @param value The desired value.
    
    void setUniform(std::string_view handle, const DrawKit::RGBA & value);
    
    /// @brief Set the value of the given uniform.
    /// @param handle The uniform's name.
    /// @param value The desired value.
    
    void setUniform(std::string_view handle, const glm::vec2 & value);
    
    /// @brief Set the value of the given uniform.
    /// @param handle The uniform's name.
    /// @param value The desired value.
    
    void setUniform(std::string_view handle, const glm::vec3 & value);
    
    /// @brief Set the value of the given uniform.
    /// @param handle The uniform's name.
    /// @param value The desired value.
    
    void setUniform(std::string_view handle, const glm::mat4 & value);
    
// MARK: - SHADER CREATION

private:
    /// @brief Compile the given GLSL source.
    /// @param type The shader's type (e.g., vertex, fragment, geometry).
    /// @param source The shader's source code.
    /// @return The shader's ID.

    uint32_t compileShader(GLenum type, const std::string & source);

    /// @brief Attach the given shaders to the given shader program and link the shader program.
    /// @param program The ID of the selected program.
    /// @param shaders The IDs of the selected, compiled shaders.

    void linkProgram(const uint32_t & program, const std::vector<GLuint> & shaders);
    
    /// @brief Create a new shader program from the given shader source files.
    /// @param vertexShaderPath The filepath of the desired vertex shader source file.
    /// @param fragmentShaderPath The filepath of the desired fragment shader source file.
    
    void createFromFiles(const std::string & vertexShaderPath,
                         const std::string & fragmentShaderPath);
    
    /// @brief Create a new shader program from the given shader source files.
    /// @param vertexShaderPath The filepath of the desired vertex shader source file.
    /// @param geometryShaderPath The filepath of the desired geometry shader source file.
    /// @param fragmentShaderPath The filepath of the desired fragment shader source file.
    
    void createFromFiles(const std::string & vertexShaderPath,
                         const std::string & geometryShaderPath,
                         const std::string & fragmentShaderPath);
    
private:
    uint32_t rendererID;
};

}

#endif
