#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 modelPosition;
uniform vec3 light;

in vec3 position;
in vec4 diffuse;
in vec4 specular;
in vec3 normal;

out vec4 fragmentDiffuse;
flat out vec3 fragmentNormal;
out vec3 fragmentLight;

void main()
{
    fragmentLight = light;
    fragmentDiffuse = diffuse;
    fragmentNormal = normalize(gl_NormalMatrix * normal);
    gl_Position = proj * view * model * vec4(position + modelPosition, 1.0);
}
