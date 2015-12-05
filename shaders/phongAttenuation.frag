#version 130

uniform float ambientIntensity;
uniform vec4 ambientColour;
uniform float directionalIntensity;
uniform vec3 directionalLight;
uniform int isInterface;

in vec3 f_normal;
in vec4 f_diffuse;
in vec4 f_specular;
in vec3 f_camera;
in vec3 f_point;

in float f_dist;
in float f_constantAttenuation;
in float f_linearAttenuation;
in float f_quadraticAttenuation;

void main()
{
    // point light attenuation
    float att = f_constantAttenuation /
                            ( ( f_linearAttenuation * f_dist ) * ( f_quadraticAttenuation * pow( f_dist, 2 ) ) );

    // diffuse
    float diffuseIntensity = 0.0;
    float directionalDiffuseIntensity = directionalIntensity * max( dot( normalize( f_normal ), -normalize( directionalLight ) ), 0.0 );
    float pointDiffuseIntensity = att * max( dot( normalize( f_normal ), f_point ), 0.0 );
    diffuseIntensity = clamp( directionalDiffuseIntensity + pointDiffuseIntensity, 0.0, 1.0 );

    // cell shading
    int cellShadingFactor = 10;
    diffuseIntensity = ceil( diffuseIntensity * cellShadingFactor ) / cellShadingFactor;

    // specular
    float specularIntensity = 0.0;
    if ( diffuseIntensity > 0.0 ) {
        vec3 reflection = normalize( directionalLight + f_camera );
        float specularAngle = max( dot( reflection, f_normal ), 0.0 );
        specularIntensity = pow( specularAngle, 100 );
        specularIntensity = ceil( specularIntensity * cellShadingFactor ) / cellShadingFactor; // cell shading
        specularIntensity = clamp( specularIntensity, 0.0, 0.8 );
    }

    // point light
    if ( diffuseIntensity > 0.0 ) {
        diffuseIntensity = clamp( diffuseIntensity, 0.0, 1.0 );
    }

    // ambient light is the darkest possible
    if ( diffuseIntensity >= 0.0 && diffuseIntensity < ambientIntensity ) {
        diffuseIntensity = ambientIntensity;
    }

    // interface elements have a minimum lighting requirement
    if ( isInterface == 1 ) {
        if ( diffuseIntensity < 0.5 ) {
            diffuseIntensity = 0.5;
        }
    }

    if ( ambientIntensity < 0.075 ) {
        gl_FragColor = ( 0.075 * f_diffuse ) + ( diffuseIntensity * f_diffuse ) + ( specularIntensity * f_specular );
    } else {
        gl_FragColor = ( ambientIntensity * f_diffuse ) + ( diffuseIntensity * f_diffuse ) + ( specularIntensity * f_specular );
    }
}
