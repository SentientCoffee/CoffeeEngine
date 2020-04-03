#type vertex
#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inUVs;
layout(location = 2) in vec4 inColour;

layout(location = 0) out vec2 outUVs;
layout(location = 1) out vec4 outColour;

uniform mat4 uViewProjection;

void main() {
	outUVs = inUVs;
	outColour = inColour;
	gl_Position = uViewProjection * vec4(inPosition, 1.0);
}

#type fragment
#version 450

layout(location = 0) in vec2 inUVs;
layout(location = 1) in vec4 inColour;

layout(location = 0) out vec4 outColour;

uniform vec4 uColour;
uniform sampler2D uTextureAlbedo;
uniform float uTileFactor;

void main() {
	//outColour = texture(uTextureAlbedo, inUVs * uTileFactor) * uColour;
	outColour = inColour;
}