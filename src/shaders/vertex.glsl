#version 330 core

layout (location=0) in vec2 vertexPos;
layout (location=1) in vec4 vertexColorA;

out vec4 fragmentColorA;

void main() {
    gl_Position = vec4(vertexPos, 0.0, 1.0);
    fragmentColorA = vertexColorA;
}