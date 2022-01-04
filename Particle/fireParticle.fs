#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;


uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 particleColor;
uniform sampler2D fireSurfaceTexture;

void main()
{   
    float ambientStrength = 0.3;
    vec3 ambient=ambientStrength*lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient+diffuse)*particleColor;
    FragColor = texture(fireSurfaceTexture, TexCoord)*vec4(result,1.0f);
}
