#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 orientation;

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
    // position
    mat4 mvp = proj * view * model;
    vec4 prePosition = orientation * vec4(scale * position, 1.0) + vec4(modelPosition, 0.0);

    gl_Position = mvp * prePosition;

    f_camera = cameraPosition;
    f_diffuse = diffuse;
    f_specular = specular;
    f_point = pointLight;
    f_normal = vec3(orientation * vec4(normalize(gl_NormalMatrix * normal), 1.0));

    // get distance to light source
    f_dist = length(vec4(pointLight, 1.0) - prePosition);

    // point lighting constants
    f_linearAttenuation = linearAtt;
    f_quadraticAttenuation = quadraticAtt;
    f_constantAttenuation = 0.05;  // its constant
}
