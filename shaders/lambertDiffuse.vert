#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 modelPosition;
uniform vec3 light;

in vec3 position;
in vec4 colour;
in vec3 normal;

out vec4 fragmentColour;
flat out vec3 fragmentNormal;
out vec3 fragmentLight;

void main()
{
    fragmentLight = light;
    fragmentColour = colour;
    fragmentNormal = normalize(gl_NormalMatrix * normal);
    gl_Position = proj * view * model * vec4(position + modelPosition, 1.0);
}
