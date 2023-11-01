#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <glad/glad.h>
#include "ztypes.h"

class Shader {
    private:
        std::string parseShaderFile(const std::string &file);
        u32 createShader(GLenum shaderType, const char *shaderSource, u32 shader);

    public:
        u32 m_shaderProgram;
        
        Shader(std::string vertexFile, std::string fragmentFile);
        ~Shader();
        void useShader();

};

#endif