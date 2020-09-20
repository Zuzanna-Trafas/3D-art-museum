#version 330

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;

out vec4 pixelColor;

in vec4 lightVector[4];
in vec4 viewerVector;
in vec4 normalVector;
in vec2 iTexCoord0;
in vec4 worldSpaceNormalVector;
in vec4 notNormalizedLightVector[4];

float distanceParameter(vec4 notNormalizedLightVector){
    float dist = length(notNormalizedLightVector);
    float maxDistance = 48.6;
    if (dist >= maxDistance){
        return 0.0;
    } else {
        return clamp(dist / maxDistance, 0, 1);
    }
}

vec4 color(vec4 lightVector, vec4 notNormalizedLightVector){
    vec4 normalizedLightVector = normalize(lightVector);
    vec4 normalizedNormalVector = normalize(normalVector);
    vec4 normalizedViewerVector = normalize(viewerVector);
    vec4 reflectedVector = reflect(-normalizedLightVector, normalizedNormalVector);

    float nl = 0;
    float rv = 0;
    vec4 kd = texture(textureMap1, iTexCoord0);
    vec4 ks = vec4(1, 1, 1, 1);

    if (distanceParameter(notNormalizedLightVector) > 0) {
        nl = clamp(dot(normalizedNormalVector, normalizedLightVector), 0, 1);

        if (worldSpaceNormalVector.y > 0) {  // sufit
            rv = pow(clamp(dot(reflectedVector, normalizedViewerVector), 0, 1), 100);
            nl = mix(1, nl, distanceParameter(notNormalizedLightVector));
        } else if (worldSpaceNormalVector.y < 0) {  // podłoga
            nl = mix(1, 0.6, distanceParameter(notNormalizedLightVector));
            if (length(notNormalizedLightVector) < 4) {
                nl = 10;
            }
        } else { //sciany
            nl = mix(1, max(nl, 0.7), distanceParameter(notNormalizedLightVector));
        }
    }
    return clamp(vec4(kd.rgb*nl, 0) + vec4(ks.rgb*rv, 0), vec4(0.0, 0.0, 0.0, 1), vec4(1, 1, 1, 1));
}

void main(void){
    pixelColor = vec4(0, 0, 0, 1);
    for (int i = 0; i < 4; i++){
        vec4 lightSourceEffect = color(lightVector[i], notNormalizedLightVector[i]);
        if (lightSourceEffect.x != 0) {
            pixelColor = lightSourceEffect;
            break;
        }
    }
}
