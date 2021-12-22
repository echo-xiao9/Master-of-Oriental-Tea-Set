//#version 330 core
//out vec4 FragColor;
//
//in vec3 Normal;
//in vec3 FragPos;
//
//uniform vec3 lightColor;
//uniform vec3 lightPos;
//uniform vec3 viewPos;
//
//void main()
//{
//    float ambientStrength = 0.4;
//    vec3 ambient= ambientStrength*lightColor;
//
//    vec3 norm = normalize(Normal);
//    vec3 lightDir = normalize(lightPos - FragPos);
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = diff * lightColor;
//
//    float specularStrength = 0.5;
//    vec3 viewDir = normalize(viewPos - FragPos);
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//    vec3 specular = specularStrength * spec * lightColor;
//
//    vec3 result = (ambient+diffuse+specular)*vec3(0.3,0.3,0.3);
//    FragColor = vec4(result,1.0f);
//}


#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = texture(texture_diffuse1, TexCoords);
}
