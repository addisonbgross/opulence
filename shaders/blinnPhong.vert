#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 modelPosition;
uniform vec3 cameraPosition;

in vec3 position;
in vec4 diffuse;
in vec4 specular;
in vec3 normal;

flat out vec3 fNormal;
out vec4 fDiffuse;
out vec4 fSpecular;
out vec3 fLightDir;
out vec3 fCamera;

void main()
{
    fCamera = cameraPosition;
    fDiffuse = diffuse;
    fSpecular = specular;
    fNormal = normalize(gl_NormalMatrix * normal);
    gl_Position = proj * view * model * vec4(position + modelPosition, 1.0);
}
