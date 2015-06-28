#version 130

uniform float ambientIntensity;
uniform vec4 ambientColour;
uniform vec3 directionalLight;

flat in vec3 fNormal;
in vec4 fDiffuse;
in vec4 fSpecular;
in vec3 fCamera;

out vec4 outColour;

void main()
{
    float diffuseIntensity = max(dot(normalize(fNormal), -directionalLight), 0.0);
    float specularIntensity = 0.0;

    if (diffuseIntensity > 0.0) {
        vec3 halfReflection = normalize(directionalLight + fCamera);
        float specularAngle = max(dot(halfReflection, fNormal), 0.0);
        specularIntensity = pow(specularAngle, 100);
    }

    if (diffuseIntensity >= 0.0 && diffuseIntensity <= ambientIntensity) {
        diffuseIntensity = ambientIntensity;
    }

    outColour = (ambientIntensity * ambientColour) + (diffuseIntensity * fDiffuse) + (specularIntensity * fSpecular);
}