#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
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
uniform Material steel;

void main()
{   
    vec3 ambient,diffuse,specular;
    vec3 color;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    if(isSurface==1.0){
        ambient=surface.ambient * lightColor;

        diffuse = (diff * surface.diffuse) * lightColor;

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), surface.shininess);
        specular = surface.specular * spec * lightColor;
        color = vec3(0.9,0.9,0.9);
    } else {
        ambient=steel.ambient * lightColor;

        diffuse = (diff * steel.diffuse) * lightColor;
        
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), steel.shininess);
        specular = steel.specular * spec * lightColor;
        color = vec3(0.87,0.87,0.87);
    }
    
    vec3 result = (ambient + diffuse + specular)*color;
    FragColor = vec4(result,1.0f);
}