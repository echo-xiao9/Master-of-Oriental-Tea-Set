#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube lake;

void main()
{    
    FragColor = texture(lake, TexCoords);
}
