/*#version 430 core

out vec4 oCol;

in vec3 ioNor;
in vec3 ioCol;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float alpha;
uniform float ambientStr;
uniform float specularStr;

void main()
{
    vec3 amb = ambientStr * lightColor;

    vec3 norm = normalize(ioNor);
    vec3 lightDir = normalize(lightPos - ioCol);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - ioCol);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStr * spec * lightColor;

    vec3 result = (amb + diffuse + specular) * objectColor;

    oCol = vec4(result, alpha);
}*/

#version 430 core
out vec4 oCol;

in vec3 ioPos;
in vec3 ioNorm;
  
uniform vec3 view_Pos;
uniform vec3 lig_pos;
uniform vec3 lig_col;
uniform vec4 iCol;
uniform float ambientV;
uniform float specularV;

void main()
{
    // ambient
    vec3 ambient = ambientV * lig_col;
  	
    // diffuse 
    vec3 norm = normalize(ioNorm);
    vec3 lightDir = normalize(lig_pos - ioPos);
    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = diff * lig_col;
    
    // specular
    vec3 viewDir = normalize(viewPos - ioPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularV * spec * lig_col;  
        
    vec3 result = (ambient + diffuse + specular) * vec3(iCol.xyz);
    cCol = vec4(result.xyz, iCol.w);
} 