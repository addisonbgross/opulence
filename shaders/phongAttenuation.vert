#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 orientation;

uniform vec3 modelPosition;
uniform vec3 cameraPosition;

// point lights
uniform int numPointLights;
uniform vec3 pointLight[];
uniform float linearAtt[];
uniform float quadraticAtt[];
uniform float constantAtt[];

uniform float scale;
uniform int isInterface;

in vec3 position;
in vec3 normal;
in vec4 diffuse;
in vec4 specular;

out vec3 f_normal;
out vec4 f_diffuse;
out vec4 f_specular;
out vec3 f_camera;

out vec3 f_pointLight;
out float f_pointDist;
out float f_linearAttenuation;
out float f_quadraticAttenuation;
out float f_constantAttenuation;

const int MAX_POINT_LIGHTS = 10;

void main()
{
    // position
    mat4 mvp = proj * view * model;
    vec4 prePosition = orientation * vec4(scale * position, 1.0) + vec4(modelPosition, 0.0);

    if ( isInterface == 1 ) {
        gl_Position = proj * prePosition;
    } else {
        gl_Position = mvp * prePosition;
    }

    f_camera = cameraPosition;
    f_diffuse = diffuse;
    f_specular = specular;
    f_normal = normalize( vec3(orientation * vec4(gl_NormalMatrix * normal, 1.0)) );

    // get distances to point lights
    float pld[MAX_POINT_LIGHTS];
    if ( numPointLights > 0 ) {
        pld[0] = length(vec4(pointLight[0], 1.0) - prePosition);
        pld[1] = length(vec4(pointLight[1], 1.0) - prePosition);
        pld[2] = length(vec4(pointLight[2], 1.0) - prePosition);
        pld[3] = length(vec4(pointLight[3], 1.0) - prePosition);
        pld[4] = length(vec4(pointLight[4], 1.0) - prePosition);
        pld[5] = length(vec4(pointLight[5], 1.0) - prePosition);
        pld[6] = length(vec4(pointLight[6], 1.0) - prePosition);
        pld[7] = length(vec4(pointLight[7], 1.0) - prePosition);
        pld[8] = length(vec4(pointLight[8], 1.0) - prePosition);
        pld[9] = length(vec4(pointLight[9], 1.0) - prePosition);
    }

    float lowestDistance = 0;
    int closestPointLight = 0;
    for (int i = 0; i < MAX_POINT_LIGHTS; ++i) {
        if (i < numPointLights) {
            if (i == 0) {
                lowestDistance = pld[0];
                closestPointLight = 0;
            } else if (pld[i] < lowestDistance) {
                lowestDistance = pld[i];
                closestPointLight = i;
            }
        }
    }

    if ( closestPointLight == 0 ) {
        f_pointLight = pointLight[0] - vec3(prePosition);
        f_pointDist = pld[0];
        f_linearAttenuation = linearAtt[0];
        f_quadraticAttenuation = quadraticAtt[0];
        f_constantAttenuation = constantAtt[0];

    } else if ( closestPointLight == 1 ) {
        f_pointLight = pointLight[1] - vec3(prePosition);
        f_pointDist = pld[1];
        f_linearAttenuation = linearAtt[1];
        f_quadraticAttenuation = quadraticAtt[1];
        f_constantAttenuation = constantAtt[1];

    } else if ( closestPointLight == 2 ) {
        f_pointLight = pointLight[2] - vec3(prePosition);
        f_pointDist = pld[2];
        f_linearAttenuation = linearAtt[2];
        f_quadraticAttenuation = quadraticAtt[2];
        f_constantAttenuation = constantAtt[2];

    } else if ( closestPointLight == 3 ) {
        f_pointLight = pointLight[3] - vec3(prePosition);
        f_pointDist = pld[3];
        f_linearAttenuation = linearAtt[3];
        f_quadraticAttenuation = quadraticAtt[3];
        f_constantAttenuation = constantAtt[3];

    } else if ( closestPointLight == 4 ) {
        f_pointLight = pointLight[4] - vec3(prePosition);
        f_pointDist = pld[4];
        f_linearAttenuation = linearAtt[4];
        f_quadraticAttenuation = quadraticAtt[4];
        f_constantAttenuation = constantAtt[4];

    } else if ( closestPointLight == 5 ) {
        f_pointLight = pointLight[5] - vec3(prePosition);
        f_pointDist = pld[5];
        f_linearAttenuation = linearAtt[5];
        f_quadraticAttenuation = quadraticAtt[5];
        f_constantAttenuation = constantAtt[5];

    } else if ( closestPointLight == 6 ) {
        f_pointLight = pointLight[6] - vec3(prePosition);
        f_pointDist = pld[6];
        f_linearAttenuation = linearAtt[6];
        f_quadraticAttenuation = quadraticAtt[6];
        f_constantAttenuation = constantAtt[6];

    } else if ( closestPointLight == 7 ) {
        f_pointLight = pointLight[7] - vec3(prePosition);
        f_pointDist = pld[7];
        f_linearAttenuation = linearAtt[7];
        f_quadraticAttenuation = quadraticAtt[7];
        f_constantAttenuation = constantAtt[7];

    } else if ( closestPointLight == 8 ) {
        f_pointLight = pointLight[8] - vec3(prePosition);
        f_pointDist = pld[8];
        f_linearAttenuation = linearAtt[8];
        f_quadraticAttenuation = quadraticAtt[8];
        f_constantAttenuation = constantAtt[8];

    } else if ( closestPointLight == 9 ) {
        f_pointLight = pointLight[9] - vec3(prePosition);
        f_pointDist = pld[9];
        f_linearAttenuation = linearAtt[9];
        f_quadraticAttenuation = quadraticAtt[9];
        f_constantAttenuation = constantAtt[9];

    } else {
        f_pointLight = vec3(0, 0, 0);
        f_pointDist = 0;
        f_linearAttenuation = 0;
        f_quadraticAttenuation = 0;
        f_constantAttenuation = 0;
    }
}
