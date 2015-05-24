#version 130

uniform vec4 ambient;
in vec4 vertexColour;

out vec4 fragColour;

void main()
{
    fragColour = min(ambient * vertexColour, vec4(1.0));
}