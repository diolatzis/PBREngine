#version 450

uniform sampler2D depthMap;
uniform sampler1D gauss;

layout(location = 0) in vec3 inColor;
layout(location = 1) in vec3 inNormalEyeSpace;
layout(location = 2) in vec4 inViewport;
layout(location = 3) in vec3 inPosEyeSpace;
layout(location = 4) in float inRadius;
layout(location = 5) in float inZNear;
layout(location = 6) in float inZFar;
layout(location = 7) in vec3 inNormal;
layout(location = 8) in mat4 inInvProj;

layout(location = 0) out vec4 color0;
layout(location = 1) out vec4 color1;

void main() 
{	
	//If the current fragment is the closest one using the depth map
	if(gl_FragCoord.z-0.0001f <= texelFetch(depthMap, ivec2(gl_FragCoord.xy), 0).x )
	{
		//Set the color with opacity from the gauss texture
		color0 = vec4(inColor, 1.0f);
		//Similarly the normals
		color1 = vec4(inNormal, 1.0f);
				
	}
	else discard;
}