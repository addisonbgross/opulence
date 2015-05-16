#version 130

in vec3 centreVertex;

void main()
{
    gl_Position = vec4( centreVertex.x, centreVertex.y, centreVertex.z, 1 );
}