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
                            ((linearAttenuation * dist) * (quadraticAttenuation * pow(dist, 2)));

    // diffuse
    float diffuseIntensity = 0.0;
    float sunDiffuseIntensity = sunIntensity * max(dot(normalize(fNormal), -sunLight), 0.0);
    float pointDiffuseIntensity = att * max(dot(normalize(fNormal), -normalize(fPoint)), 0.0);
    diffuseIntensity = clamp(sunDiffuseIntensity + pointDiffuseIntensity, 0.0, 1.0);

    // cell shading
    int cellShadingFactor = 10;
    diffuseIntensity = ceil(diffuseIntensity * cellShadingFactor) / cellShadingFactor;

    // specular
    float specularIntensity = 0.0;
    if (diffuseIntensity > 0.0) {
        vec3 reflection = normalize(sunLight + fCamera);
        float specularAngle = max(dot(reflection, fNormal), 0.0);
        specularIntensity = pow(specularAngle, 100);
        specularIntensity = ceil(specularIntensity * cellShadingFactor) / cellShadingFactor; // cell shading
        specularIntensity = clamp(specularIntensity, 0.0, 0.3);
    }

    // point light
    if (diffuseIntensity > 0.0) {
        diffuseIntensity = clamp(diffuseIntensity, 0.0, 1.0);
    }

    // ambient light is the darkest possible
    if (diffuseIntensity >= 0.0 && diffuseIntensity < ambientIntensity) {
        diffuseIntensity = ambientIntensity;
    }

    outColour = (ambientIntensity * fDiffuse) + (diffuseIntensity * fDiffuse) + (specularIntensity * fSpecular);
}