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

in vec3 position;
in vec3 normal;
in vec4 diffuse;
in vec4 specular;

flat out vec3 fNormal;
out vec4 fDiffuse;
out vec4 fSpecular;
out vec3 fCamera;
out vec3 fPoint;

out float dist;
out float constantAttenuation;
out float linearAttenuation;
out float quadraticAttenuation;

void main()
{
    fCamera = cameraPosition;
    fDiffuse = diffuse;
    fSpecular = specular;
    fNormal = normalize(gl_NormalMatrix * normal);
    fPoint = pointLight;

    // get distance to light source
    dist = length(pointLight - (position + modelPosition));

    // point lighting constants
    linearAttenuation = linearAtt;
    quadraticAttenuation = quadraticAtt;
    constantAttenuation = 0.1;  // its constant

    gl_Position = proj * view * model * vec4(position + modelPosition, 1.0);
}
