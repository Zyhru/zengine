#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;


void main() {
    gl_Position = vec4(aPos, 1.0f); 
    vertexColor = vec4(0.1333f, 0.545f, 0.1333f, 1.0);
}


