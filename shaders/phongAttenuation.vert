#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 modelPosition;
uniform vec3 cameraPosition;
uniform vec3 pointLight;

// point light attenuation
uniform float linearAtt;
uniform float quadraticAtt;

uniform float scale;

in vec3 position;
in vec3 normal;
in vec4 diffuse;
in vec4 specular;

out vec3 f_normal;
out vec4 f_diffuse;
out vec4 f_specular;
out vec3 f_camera;
out vec3 f_point;

out float f_dist;
out float f_constantAttenuation;
out float f_linearAttenuation;
out float f_quadraticAttenuation;

void main()
{
    f_camera = cameraPosition;
    f_diffuse = diffuse;
    f_specular = specular;
    f_normal = normalize(gl_NormalMatrix * normal);
    f_point = pointLight;

    // get distance to light source
    f_dist = length(pointLight - (position + modelPosition));

    // point lighting constants
    f_linearAttenuation = linearAtt;
    f_quadraticAttenuation = quadraticAtt;
    f_constantAttenuation = 0.05;  // its constant

    gl_Position = proj * view * model * vec4(scale * position + modelPosition, 1.0);
}
