#version 330 core
out vec4 FragColor;

uniform vec4 cColor;

uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = cColor;
}