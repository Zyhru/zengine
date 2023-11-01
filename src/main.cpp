#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ztypes.h"
#include "shader.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

float vertexData[] = {
    0.5f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f, 0.0f, 
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    std::cout << "Resizing window" << std::endl;
    glViewport(0,0,width,height);
}

void key_input_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    if(window == NULL) {
        std::cout << "Could not load window" << std::endl;
        return;
    }

    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_ESCAPE:
                std::cout << "Closing Window" << std::endl;
                break;
            case GLFW_KEY_W:
                std::cout << "W" << std::endl;
                break;
            case GLFW_KEY_A:
                std::cout << "A" << std::endl;
                break;
            case GLFW_KEY_S:
                std::cout << "S" << std::endl;
                break;
            case GLFW_KEY_D:
                std::cout << "D" << std::endl;
                break;
        }
    }
}

void render(Shader& s, u32 v) {
    s.useShader();
    glBindVertexArray(v);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Renderer", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
 
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_input_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0,WIN_WIDTH,WIN_HEIGHT);

    // Loading shader code
    Shader shader("C:\\zengine\\vertex.vert", "C:\\zengine\\fragment.frag");

    // Upload vertex data to GPU (color, texture, position)
    u32 VAO; // Vertex Array Object
    u32 VBO; // Vertex Buffer Object
    u32 EBO; // Index buffer

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);  

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // Setting vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        render(shader, VAO);
       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    glfwTerminate();
    return 0;
}