#version 130

uniform float ambientIntensity;
uniform vec4 ambientColour;
uniform float sunIntensity;
uniform vec3 sunLight;

flat in vec3 fNormal;
in vec4 fDiffuse;
in vec4 fSpecular;
in vec3 fCamera;
in vec3 fPoint;

in float dist;
in float constantAttenuation;
in float linearAttenuation;
in float quadraticAttenuation;

out vec4 outColour;

void main()
{
    // point light attenuation
    float att = constantAttenuation /
                            ((1 + linearAttenuation * dist) * (1 + quadraticAttenuation * pow(dist, 2)));

    // diffuse
    float diffuseIntensity = 0.0;
    diffuseIntensity = max(dot(normalize(fNormal), -sunLight), 0.0);

    // specular
    float specularIntensity = 0.0;
    if (diffuseIntensity > 0.0) {
        vec3 halfReflection = normalize(sunLight + fCamera);
        float specularAngle = max(dot(halfReflection, fNormal), 0.0);
        specularIntensity = pow(specularAngle, 100);
    }

    // point light
    float incidentAngle = max(dot(normalize(fNormal), -normalize(fPoint)), 0.0);
    //if (incidentAngle > 0.0) {
        diffuseIntensity = clamp(diffuseIntensity + att, 0.0, 1.0);
    //}

    // ambient light is the darkest possible
    if (diffuseIntensity > 0.0 && diffuseIntensity < ambientIntensity) {
        diffuseIntensity = ambientIntensity;
    }

    outColour = (ambientIntensity * fDiffuse) + (diffuseIntensity * fDiffuse) + (specularIntensity * fSpecular);
}