#include <fstream>
#include "shader.h"

#define NEWLINE "\n"

Shader::Shader(std::string vertexFile, std::string fragmentFile) {
    
    std::string vertexSource   = parseShaderFile(vertexFile);
    std::string fragmentSource = parseShaderFile(fragmentFile); // failing

    #if 0 
    printf("Vertex Source: %s\n", vertexSource.c_str());
    printf("Fragment Source: %s\n", fragmentSource.c_str());
    #endif

    u32 vertexShader, fragmentShader;
    vertexShader   = createShader(GL_VERTEX_SHADER, vertexSource.c_str(), vertexShader);
    fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSource.c_str(), fragmentShader);
    
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

Shader::~Shader() {
    std::cout << "Destroying shader object" << NEWLINE;
}

std::string Shader::parseShaderFile(const std::string &file) {
    std::fstream inputFile(file);
    if(!inputFile.is_open()) return "[ERR] Could not open file";

    std::string line;
    std::string shaderSource;

    while(std::getline(inputFile, line)) {
        shaderSource.append(line);
        shaderSource.append("\n");
    }

    // printf("%s\n", shaderSource.c_str());
    inputFile.close();

    return shaderSource;
}


u32 Shader::createShader(GLenum shaderType, const char *shaderSource, u32 shader) {

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // TODO: Check for errors 

    return shader;

}

void Shader::useShader() {
    glUseProgram(m_shaderProgram);
}
