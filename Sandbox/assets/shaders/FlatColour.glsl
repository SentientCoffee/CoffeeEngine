#type vertex
#version 450

layout(location = 0) in vec3 inPosition;

uniform mat4 uViewProjection;
uniform mat4 uModelMatrix;

void main() {
	gl_Position = uViewProjection * uModelMatrix * vec4(inPosition, 1.0);
}


#type fragment
#version 450

layout(location = 0) out vec4 outColour;

uniform vec4 uColour;

void main() {
	outColour = uColour;
}