#version 130

uniform float ambientIntensity;
uniform vec4 ambientColour;
uniform float directionalIntensity;
uniform vec3 directionalLight;
uniform int isHighlight;
uniform int numPointLights;

in vec3 f_normal;
in vec4 f_diffuse;
in vec4 f_specular;
in vec3 f_camera;

in vec3 f_pointLight;
in float f_pointDist;
in float f_linearAttenuation;
in float f_quadraticAttenuation;
in float f_constantAttenuation;

void main()
{
    // point light attenuation
    float plAttenuation = f_constantAttenuation /
                            ( ( f_linearAttenuation * f_pointDist ) * ( f_quadraticAttenuation * pow( f_pointDist, 2 ) ) );

    // diffuse
    float diffuseIntensity = 0.0;
    float directionalDiffuseIntensity = directionalIntensity * max( dot( normalize( f_normal ), -normalize( directionalLight ) ), 0.0 );

    // apply closest point light
    if ( numPointLights > 0 && directionalDiffuseIntensity < 0.7 ) {
        float pointDiffuseIntensity = plAttenuation * max( dot( normalize( f_normal ), f_pointLight ), 0.0 );
        diffuseIntensity = clamp( directionalDiffuseIntensity + pointDiffuseIntensity, 0.0, 1.0 );
    } else {
        diffuseIntensity = clamp( directionalDiffuseIntensity, 0.0, 1.0 );
    }

    // cell shading
    int cellShadingFactor = 8;
    diffuseIntensity = ceil( diffuseIntensity * cellShadingFactor ) / cellShadingFactor;

    // specular
    float specularIntensity = 0.0;
    if ( diffuseIntensity > 0.0 ) {
        vec3 reflection = normalize( directionalLight + f_camera );
        float specularAngle = max( dot( reflection, f_normal ), 0.0 );
        specularIntensity = pow( specularAngle, 50 );
        specularIntensity = ceil( specularIntensity * cellShadingFactor ) / cellShadingFactor; // cell shading
    }

    // ambient light is the darkest possible
    if ( diffuseIntensity >= 0.0 && diffuseIntensity < ambientIntensity ) {
        diffuseIntensity = ambientIntensity;
    }

    // ui elements have a minimum lighting requirement
    if ( isHighlight == 1 ) {
        if ( diffuseIntensity < 0.75 ) {
            diffuseIntensity = 0.75;
        }
    }

    if ( ambientIntensity < 0.05 ) {
        gl_FragColor = ( 0.05 * f_diffuse ) + ( diffuseIntensity * f_diffuse ) + ( specularIntensity * f_specular );
    } else {
        gl_FragColor = ( ambientIntensity * f_diffuse ) + ( diffuseIntensity * f_diffuse ) + ( specularIntensity * f_specular );
    }
}
