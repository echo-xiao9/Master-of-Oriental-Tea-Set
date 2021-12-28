#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube fire;

void main()
{    
    FragColor = texture(fire, TexCoords);
}
