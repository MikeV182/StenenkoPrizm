#version 330 core

out vec4 FragColor;

in vec3 color; // input variable with the same name and the same type from 'default.vert'

void main()
{
   FragColor = vec4(color, 1.0f);
}