#version 430 core

out vec4 oCol;

in vec3 ioPos;
in vec3 ioNorm;

uniform vec3 lig_pos;
uniform vec3 lig_col;
uniform vec4 iCol;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lig_col;
  	
    // diffuse 
    vec3 norm = normalize(ioNorm);
    vec3 lightDir = normalize(lig_pos * ioPos);
    float diff = dot(norm, lightDir);
    vec3 diffuse = vec3(diff, diff, diff) * lig_col;
            
    vec3 result = (ambient + diffuse) * vec3(iCol.xyz);
    oCol = vec4(result, 1.0) + vec4(1.0, 1.0, 1.0, 1.0);
}