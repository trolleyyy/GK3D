#version 150 core

uniform vec3 objectColor;
uniform vec3 lightColor;
out vec4 color;

void main()
{
    color = vec4(lightColor * objectColor, 1.0f);
}