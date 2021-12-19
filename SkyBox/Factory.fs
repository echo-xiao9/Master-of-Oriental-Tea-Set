#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube factory;

void main()
{    
    FragColor = texture(factory, TexCoords);
}