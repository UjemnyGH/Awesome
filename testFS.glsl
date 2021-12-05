#version 430 core

in vec4 ioPos;

out vec4 oCol;

uniform vec4 iCol;
uniform sampler2D tex;

in vec2 ioTex;

void main()
{
    vec3 res = dot(vec3(ioPos.xyz), vec3(iCol.xyz)) * vec3(iCol.xyz) * vec3(1.0, 1.0, 1.0);
    oCol = vec4(res.xyz, 1.0);
    //oCol = distance(vec4(1.0, dot(ioPos, iCol) - noise1(iCol), 1.0, 1.0), iCol) * iCol * vec4(1.0, 1.0, 1.0, 1.0);

    //oCol = texture(tex, ioTex) * vec4(cross(vec3(ioPos.x, ioTex.y, ioPos.z), vec3(ioTex.x, iCol.y, iCol.z)), 1.0);
    //oCol = texture(tex, ioTex) * dot(ioPos, vec4(4.0, 0.0, 0.0, 1.0));

    /*vec3 lightDir = normalize(ioPos * iCol);
    float diff = dot(iCol, vec4(lightDir, 1.0));
    vec3 diffuse1 = ioPos * diff;

    oCol = vec4(diffuse1.x, diffuse1.y, diffuse1.z, 1.0);*/
}