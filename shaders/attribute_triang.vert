#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

layout(location = 0) in vec3 inPos;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoords;

layout(location = 0) out vec2 outTexCoords;
layout(location = 1) out vec3 outNormal;

out gl_PerVertex 
{
    vec4 gl_Position;
	float gl_PointSize;
};

void main() 
{
	//Compute position in clip coordinates
	gl_Position = proj * view * model * vec4(inPos,1.0f);

	outTexCoords = inTexCoords;
	outNormal = inNormal;
}