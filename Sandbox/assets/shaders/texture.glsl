#type vertex
#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inUVs;

layout(location = 0) out vec2 outUVs;

uniform mat4 uViewProjection;
uniform mat4 uModelMatrix;

void main() {
	outUVs = inUVs;
	gl_Position = uViewProjection * uModelMatrix * vec4(inPosition, 1.0);
}


#type fragment
#version 450

layout(location = 0) in vec2 inUVs;

layout(location = 0) out vec4 outColour;

uniform vec4 uColour;
uniform sampler2D uTextureAlbedo;
uniform float uTileFactor;

void main() {
	outColour = texture(uTextureAlbedo, inUVs * uTileFactor) * uColour;
}