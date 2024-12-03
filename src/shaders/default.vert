#version 330 core
layout (location = 0) in vec3 aPos; // position with attribute position set to zero
layout (location = 1) in vec3 aColor;

out vec3 color; // specifying a color output to the fragment shader

uniform float scale; // never write uniforms if you not planning to use them
                     // otherwise OpenGL will delete them automaticaly and that may cause errors

void main()
{
   gl_Position = vec4(aPos.x + aPos.x * scale, 
                      aPos.y + aPos.y * scale,
                      aPos.z + aPos.z * scale,
                      1.0); // giving vec3 to constructor of vec4
   color = aColor;
}