#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube forest;

void main()
{    
    FragColor = texture(forest, TexCoords);
}