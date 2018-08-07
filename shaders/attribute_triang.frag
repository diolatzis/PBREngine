#version 450

uniform sampler2D depthMap;
uniform sampler2D texture;

layout(location = 0) in vec2 inTexCoords;
layout(location = 1) in vec3 inNormal;

layout(location = 0) out vec4 color0;
layout(location = 1) out vec4 color1;

void main() 
{		
	//If the current fragment is the closest one using the depth map
	if(gl_FragCoord.z-0.0001f <= texelFetch(depthMap, ivec2(gl_FragCoord.xy), 0).x )
	{
		color0 = texelFetch(texture, ivec2(inTexCoords.xy), 0);
		color1 = vec4(inNormal, 1.0f);
	}
	else discard;
}