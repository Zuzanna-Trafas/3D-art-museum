#version 330

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;

out vec4 pixelColor;

in vec4 lightVector[4];
in vec4 notNormalizedVector[4];
in vec4 viewerVector;
in vec4 normalVector;
in vec2 iTexCoord0;

float distanceParameter(vec4 notNormalizedVector){
	float dist = length(notNormalizedVector);
	if (dist >= 100){
		return 0.0;
	}
	else{
		return (1- (dist / 100));
	}
}

vec4 color(vec4 lightVector, vec4 notNormalizedVector){
	vec4 normalizedLightVector = normalize(lightVector);
	vec4 normalizedNormalVector = normalize(normalVector);
	vec4 normalizedViewerVector = normalize(viewerVector);
	
	vec4 reflectedVector = reflect(-normalizedLightVector, normalizedNormalVector);
	
	vec4 kd = texture(textureMap1, iTexCoord0);
	vec4 ks = vec4(0, 0, 0, 1);
	
	float nl = clamp(abs(dot(normalizedNormalVector, normalizedLightVector)), 0, 1);
	float rv = pow(clamp(dot(reflectedVector, normalizedViewerVector), 0, 1), 100);

	nl = mix(nl, 0, distanceParameter(notNormalizedVector));
	
	return vec4(kd.rgb*nl, 0) + vec4(ks.rgb*rv, 0);

}

void main(void){
	pixelColor = vec4(0, 0, 0, 1);
	for (int i = 0; i < 4; i++){
		pixelColor += color(lightVector[i], notNormalizedVector[i]);
	}
	pixelColor = clamp(pixelColor, vec4(0, 0, 0, 0), vec4(1, 1, 1, 1));
}
