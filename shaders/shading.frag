#version 450

uniform sampler2D colorTex;
uniform sampler2D normalTex;
uniform sampler2D depthMap;
uniform sampler2D shadowMap;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec4 inPosLightSpace;
layout(location = 2) in vec3 inLightPos;
layout(location = 3) in vec3 inAmbient;
layout(location = 4) in vec3 inDiffuse;
layout(location = 5) in vec3 inSpecular;
layout(location = 6) in float inSpecularPower;
layout(location = 7) in mat4 inViewModel;

layout(location = 0) out vec4 outColor;




void main() 
{	

	//If the current fragment is the closest one using the depth map
	if(gl_FragCoord.z - 0.0001f < texelFetch(depthMap, ivec2(gl_FragCoord.xy), 0).x)
	{
		
		//Get the color and normal information from the textures
		vec4 color = texelFetch(colorTex, ivec2(gl_FragCoord.xy), 0);
		vec4 normal = texelFetch(normalTex, ivec2(gl_FragCoord.xy), 0);
		
		
		if(inPosLightSpace.z-0.008 > texelFetch(shadowMap, ivec2(inPosLightSpace.xy), 0).x)
		{
			outColor = vec4(color.xyz*(inAmbient), color.w);
		}
		else
		{
			//Compute Phong model ambient diffuse and specular
			vec4 P = inViewModel*vec4(inPos, 1.0f);
			vec3 N = mat3(inViewModel)* normal.xyz;
			
			vec3 L = inLightPos - P.xyz;
			vec3 V = -P.xyz;
			
			N = normalize(N);
			L = normalize(L);
			V = normalize(V);
			
			vec3 R = reflect(-L, N);
			
			vec3 diffuse = max(dot(N, L), 0.0) *inDiffuse;
			vec3 specular = pow(max(dot(R, V), 0.0), inSpecularPower) * inSpecular;
			
			outColor = vec4(color.xyz*(inAmbient + diffuse + specular), color.w);
		}
	}
	else discard;	
}