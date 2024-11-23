#pragma once

#include <WillowVoxEngine/Rendering/Shader.h>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <WillowVoxEngine/Core/Logger.h>

namespace WillowVox
{
    Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexShaderPath);
            fShaderFile.open(fragmentShaderPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            Logger::Error("Error reading shader source files: %s", e.what());
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        // print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            Logger::Error("Error compiling vertex shader! (%s): %s", vertexShaderPath, infoLog);
        }

        // fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        // print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            Logger::Error("Error compiling fragment shader! (%s): %s", fragmentShaderPath, infoLog);
        }

        // shader program
        programId = glCreateProgram();
        glAttachShader(programId, vertex);
        glAttachShader(programId, fragment);
        glLinkProgram(programId);
        // print linking errors if any
        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(programId, 512, nullptr, infoLog);
            Logger::Error("Error linking shader program: %s", infoLog);
        }

        // delete the shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader::~Shader()
    {
        glDeleteProgram(programId);
    }

    void Shader::Use()
    {
        glUseProgram(programId);
    }

    void Shader::SetBool(const char* name, bool value) const
    {
        glUniform1i(glGetUniformLocation(programId, name), (int)value);
    }

    void Shader::SetInt(const char* name, int value) const
    {
        glUniform1i(glGetUniformLocation(programId, name), value);
    }

    void Shader::SetFloat(const char* name, float value) const
    {
        glUniform1f(glGetUniformLocation(programId, name), value);
    }

    void Shader::SetVec2(const char* name, glm::vec2 value) const
    {
        glUniform2f(glGetUniformLocation(programId, name), value.x, value.y);
    }

    void Shader::SetVec2(const char* name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(programId, name), x, y);
    }

    void Shader::SetVec3(const char* name, glm::vec3 value) const
    {
        glUniform3f(glGetUniformLocation(programId, name), value.x, value.y, value.z);
    }

    void Shader::SetVec3(const char* name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(programId, name), x, y, z);
    }

    void Shader::SetMat4(const char* name, glm::mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(programId, name), 1, GL_FALSE, glm::value_ptr(value));
    }
}