#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 transform;
uniform mat4 view;

void main()
{
    gl_Position = transform * view * vec4(aPos, 1.0);
}


