#type vertex
#version 450

layout(location = 0) in vec3  inPosition;
layout(location = 1) in vec4  inColour;
layout(location = 2) in vec2  inUV;
layout(location = 3) in float inUVIndex;
layout(location = 4) in float inTileFactor;

layout(location = 0) out vec4  outColour;
layout(location = 1) out vec2  outUV;
layout(location = 2) out float outUVIndex;
layout(location = 3) out float outTileFactor;

uniform mat4 uViewProjection;

void main() {
	gl_Position = uViewProjection * vec4(inPosition, 1.0);
	
	outColour = inColour;
	outUV = inUV;
	outUVIndex = inUVIndex;
	outTileFactor = inTileFactor;
}

#type fragment
#version 450

layout(location = 0) in vec4  inColour;
layout(location = 1) in vec2  inUV;
layout(location = 2) in float inUVIndex;
layout(location = 3) in float inTileFactor;

layout(location = 0) out vec4 outColour;

uniform sampler2D uTextures[32];

void main() {
	outColour = texture(uTextures[int(inUVIndex)], inUV * inTileFactor) * inColour;
}