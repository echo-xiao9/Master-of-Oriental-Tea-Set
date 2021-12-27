//#version 330 core
//out vec4 FragColor;
//
//in vec3 Normal;
//in vec3 FragPos;
//in vec2 TexCoord;
//flat in float isSurface;
//
//struct Material {
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//    float shininess;
//};
//
//uniform vec3 lightColor;
//uniform vec3 lightPos;
//uniform vec3 viewPos;
//uniform Material surface;
//uniform Material wood;
//uniform sampler2D woodTexture;
//uniform sampler2D surfaceTexture;
//
//void main()
//{
//    vec3 ambient,diffuse,specular;
//    vec3 color;
//    vec3 norm = normalize(Normal);
//    vec3 lightDir = normalize(lightPos - FragPos);
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 viewDir = normalize(viewPos - FragPos);
//    vec3 reflectDir = reflect(-lightDir, norm);
//
//    if(isSurface==1.0){
//        ambient=surface.ambient * lightColor;
//
//        diffuse = (diff * surface.diffuse) * lightColor;
//
//        float spec = pow(max(dot(viewDir, reflectDir), 0.0), surface.shininess);
//        specular = surface.specular * spec * lightColor;
//
//        vec3 result = (ambient + diffuse + specular);
//        FragColor = texture(surfaceTexture, TexCoord)*vec4(result,1.0);
//    }else {
//        ambient=wood.ambient * lightColor;
//
//        diffuse = (diff * wood.diffuse) * lightColor;
//
//        float spec = pow(max(dot(viewDir, reflectDir), 0.0), wood.shininess);
//        specular = wood.specular * spec * lightColor;
//
//        vec3 result = (ambient + diffuse + specular);
//        FragColor = texture(woodTexture, TexCoord)*vec4(result,1.0);
//    }
//
//
//}


#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
flat in float isSurface;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material surface;
uniform Material wood;
uniform sampler2D woodTexture;
uniform sampler2D surfaceTexture;
uniform sampler2D woodNormalMap;


void main()
{
    vec3 ambient,diffuse,specular;
    vec3 color;
//    vec3 norm = normalize(Normal);
    vec3 norm = texture(woodNormalMap, TexCoord).rgb;
    norm = normalize(norm * 2.0 - 1.0);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    
    if(isSurface==1.0){
        ambient=surface.ambient * lightColor;

        diffuse = (diff * surface.diffuse) * lightColor;

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), surface.shininess);
        specular = surface.specular * spec * lightColor;
        
        vec3 result = (ambient + diffuse + specular);
        FragColor = texture(surfaceTexture, TexCoord)*vec4(result,1.0);
    }else {
        ambient=wood.ambient * lightColor;

        diffuse = (diff * wood.diffuse) * lightColor;
        
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), wood.shininess);
        specular = wood.specular * spec * lightColor;

        vec3 result = (ambient + diffuse + specular);
        FragColor = texture(woodTexture, TexCoord)*vec4(result,1.0);
    }
    

}
