#version 450

layout(location = 0) in vec3 inColor;
layout(location = 1) in vec3 inNormalEyeSpace;
layout(location = 2) in vec4 inViewport;
layout(location = 3) in vec3 inPosEyeSpace;
layout(location = 4) in mat4 inInvProj;

layout(location = 0) out vec4 outColor;

void main() 
{	

	vec4 ndcPos;
	ndcPos.xy = ((2.0 * gl_FragCoord.xy) - (2.0 * inViewport.xy)) / (inViewport.zw) - 1;
	ndcPos.z = (2.0 * gl_FragCoord.z - gl_DepthRange.near - gl_DepthRange.far) / (gl_DepthRange.far - gl_DepthRange.near);
	ndcPos.w = 1.0;

	vec4 clipPos = ndcPos / gl_FragCoord.w;
	vec4 eyePos = inInvProj * clipPos;	
	
	vec3 q = eyePos.xyz * (dot(inPosEyeSpace, inNormalEyeSpace)/dot(eyePos.xyz, inNormalEyeSpace));
	
	if(length(q-inPosEyeSpace) <= 0.1f )
	{
		outColor = vec4(inColor, 1.0f);
	}
	else discard;	
	
}