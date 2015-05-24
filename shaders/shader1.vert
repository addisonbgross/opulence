#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec3 position;
in vec4 colour;

out vec4 vertexColour;

void main()
{
    vertexColour = colour;
    gl_Position = proj * view * model * vec4(position, 1.0);
}
