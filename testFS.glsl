#version 430 core

in vec3 ioPos;
in vec2 ioTex;
in vec3 ioNorm;

out vec4 oCol;

uniform vec4 iCol;
uniform sampler2D tex;

void main()
{
    /*vec3 res = dot(vec3(ioPos.xyz), vec3(iCol.xyz)) * vec3(iCol.xyz) * vec3(1.0, 1.0, 1.0);
    oCol = vec4(res.xyz, 1.0);*/
    //oCol = distance(vec4(1.0, dot(ioPos, iCol) - noise1(iCol), 1.0, 1.0), iCol) * iCol * vec4(1.0, 1.0, 1.0, 1.0);

    //oCol = texture(tex, ioTex) * vec4(cross(vec3(ioPos.x, ioTex.y, ioPos.z), vec3(ioTex.x, iCol.y, iCol.z)), 1.0);
    //oCol = texture(tex, ioTex) * dot(ioPos, vec4(4.0, 0.0, 0.0, 1.0));

    float ambientStrength = 0.4;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);
  	
    // diffuse 
    vec3 norm = normalize(ioNorm);
    vec3 lightDir = normalize(vec3(1.0, 0.0, 1.0) * ioPos);
    float diff = dot(norm, lightDir);
    vec3 diffuse = vec3(diff, diff, diff) * vec3(1.0, 1.0, 1.0);
            
    vec3 result = (ambient + diffuse) * vec3(iCol.xyz);
    oCol = vec4(result, iCol.w);
}