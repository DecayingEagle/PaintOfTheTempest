#version 330 core

in vec4 fragmentColorA;

out vec4 screenColor;

void main(){
    screenColor = vec4(fragmentColorA);
}