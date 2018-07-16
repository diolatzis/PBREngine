#version 450

layout(location = 0) in vec3 inColor;
layout(location = 1) in vec3 inNormalEyeSpace;
layout(location = 2) in vec4 inViewport;
layout(location = 3) in vec3 inPosEyeSpace;
layout(location = 4) in mat4 inInvProj;

layout(location = 0) out vec4 outColor;

void main() 
{	

	outColor = vec4(inColor, 1.0f);
	
}