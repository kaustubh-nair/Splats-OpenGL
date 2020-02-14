#version 330 core

out vec4 FragColor;

uniform vec3 vertexColor;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(lightColor * vertexColor, 1.0);
    
}


