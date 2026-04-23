#version 330 core 

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
    vec3 norm = normalize(Normal);

    // ambient
    vec3 ambient = 0.2 * vec3(1.0);

    // diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0);

    // specular 
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = 0.5 * spec * vec3(1.0);
    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}