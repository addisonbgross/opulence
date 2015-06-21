#version 130

uniform vec4 ambient;

in vec4 fragmentDiffuse;
flat in vec3 fragmentNormal;
in vec3 fragmentLight;

out vec4 outColour;

void main()
{
     float diffuse = max(dot(normalize(fragmentNormal), -fragmentLight), 0.0);
     outColour = fragmentDiffuse * (diffuse + ambient);
 }