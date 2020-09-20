#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lightSource;

layout (location = 0) in vec4 vertex;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec2 texCoord0;

out vec4 lightVector[4];
out vec4 viewerVector;
out vec4 normalVector;
out vec2 iTexCoord0;
out vec4 worldSpaceNormalVector;
out vec4 notNormalizedLightVector[4];

void main(void){
	vec4 vertex4 = vertex;
	vec4 normal4 = normal;

	notNormalizedLightVector[0] = V*vec4(45, 9, 45, 1) - V*M*vertex4;
	notNormalizedLightVector[1] = V*vec4(-45, 9, 45, 1) - V*M*vertex4;
	notNormalizedLightVector[2] = V*vec4(-45, 9, -45, 1) - V*M*vertex4;
	notNormalizedLightVector[3] = V*vec4(45, 9, -45, 1) - V*M*vertex4;

	lightVector[0] = normalize(notNormalizedLightVector[0]);
	lightVector[1] = normalize(notNormalizedLightVector[1]);
	lightVector[2] = normalize(notNormalizedLightVector[2]);
	lightVector[3] = normalize(notNormalizedLightVector[3]);
	viewerVector = normalize(vec4(0, 0, 0, 1) - V*M*vertex4);
	worldSpaceNormalVector = M*normal4;
	normalVector = normalize(V*M*normal4);
	iTexCoord0 = texCoord0;
	gl_Position = P*V*M*vertex4;
}
