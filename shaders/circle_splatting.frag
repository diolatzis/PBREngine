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
	//First we compute the position of the point on the near plane 
	//that is being projected to the current window pixel
	vec4 ndcPos;
	ndcPos.xy = ((2.0 * gl_FragCoord.xy) - (2.0 * inViewport.xy)) / (inViewport.zw) - 1;
	ndcPos.z = (2.0 * gl_FragCoord.z - gl_DepthRange.near - gl_DepthRange.far) / (gl_DepthRange.far - gl_DepthRange.near);
	ndcPos.w = 1.0;

	vec4 clipPos = ndcPos / gl_FragCoord.w;
	vec4 eyePos = inInvProj * clipPos;	

	//Then we compute the position of the point on the supporting plane of the splat
	vec3 q = eyePos.xyz * (dot(inPosEyeSpace, inNormalEyeSpace)/dot(eyePos.xyz, inNormalEyeSpace));

	//We compute the depth in the range of near and far Z
	float z = (1/q.z)*((inZFar*inZNear)/(inZFar-inZNear))+(inZFar/(inZFar-inZNear));
	
	//Set the correct depth of the fragment
	gl_FragDepth = z;
	
	//If the current fragment is the closest one using the depth map
	if(z-0.00005f <= texelFetch(depthMap, ivec2(gl_FragCoord.xy), 0).x )
	{
		//If the point on the supporting plane is within the range of the splat
		if(length(q-inPosEyeSpace) <= inRadius )
		{
			//Compute the distance in a range 0-1
			float t = ((length(q-inPosEyeSpace) / inRadius));
			int m = int(t*20);
			//Set the color with opacity from the gauss texture
			color0 = vec4(inColor, texelFetch(gauss, m, 0).x);
			//Similarly the normals
			color1 = vec4(inNormal, texelFetch(gauss, m, 0).x);
		}
		else discard;		
	}
	else discard;
		

	
	
	
}