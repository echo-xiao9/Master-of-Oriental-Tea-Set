#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in float aRadius;
layout (location = 3) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec3 cColor;
flat out float isSurface;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 rotate;

void main()
{
    gl_Position = projection * view * model * rotate * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = vec3(rotate * vec4(aNormal, 1.0));
    isSurface = (aRadius==1.5f)?1.0:0.0;
}