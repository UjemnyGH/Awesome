#version 430 core

in vec3 ioPos;
in vec2 ioTex;
in vec3 ioNorm;

out vec4 oCol;

uniform vec4 iCol;
uniform sampler2D tex;

uniform vec3 viewPos;
uniform vec3 lig_pos;
uniform vec3 lig_col;
uniform float ambientV;
uniform float specularV;

void main()
{
    /*vec3 res = dot(vec3(ioPos.xyz), vec3(iCol.xyz)) * vec3(iCol.xyz) * vec3(1.0, 1.0, 1.0);
    oCol = vec4(res.xyz, 1.0);*/
    //oCol = distance(vec4(1.0, dot(ioPos, iCol) - noise1(iCol), 1.0, 1.0), iCol) * iCol * vec4(1.0, 1.0, 1.0, 1.0);

    //oCol = texture(tex, ioTex) * vec4(cross(vec3(ioPos.x, ioTex.y, ioPos.z), vec3(ioTex.x, iCol.y, iCol.z)), 1.0);
    //oCol = texture(tex, ioTex) * dot(ioPos, vec4(4.0, 0.0, 0.0, 1.0));

    vec3 ambient = ambientV * lig_col;
  	
    // diffuse 
    vec3 norm = normalize(ioNorm);
    vec3 lightDir = normalize(lig_pos * ioPos);
    float diff = dot(norm, lightDir);
    vec3 diffuse = vec3(diff, diff, diff) * lig_col;

    vec3 viewDir = normalize(viewPos - ioPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularV * spec * lig_col; 
            
    vec3 result = (ambient + diffuse + specular) * vec3(iCol.xyz);
    vec4 outCol = texture(tex, ioTex) * vec4(result, iCol.w);
    if(outCol.a < 0.1)
        discard;

    oCol = outCol;
}