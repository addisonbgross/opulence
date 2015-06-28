#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 modelPosition;
uniform vec3 cameraPosition;
uniform vec3 pointLight;

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

    // poor attenuation values
    if (dist < 7.0) {
        linearAttenuation = 0.7;
        quadraticAttenuation = 1.8;
    } else if (dist < 13.0) {
        linearAttenuation = 0.35;
        quadraticAttenuation = 0.44;
    } else if (dist < 20.0) {
        linearAttenuation = 0.22;
        quadraticAttenuation = 0.20;
    }

    if (dist < 32.0) {
        linearAttenuation = 0.14;
        quadraticAttenuation = 0.07;
    }

    if (dist < 50.0) {
        linearAttenuation = 0.09;
        quadraticAttenuation = 0.32;
    }

    if (dist < 65.0) {
        linearAttenuation = 0.07;
        quadraticAttenuation = 0.017;
    }

    if (dist < 100.0) {
        linearAttenuation = 0.045;
        quadraticAttenuation = 0.0075;
    }

    constantAttenuation = 1.0;
    gl_Position = proj * view * model * vec4(position + modelPosition, 1.0);
}
