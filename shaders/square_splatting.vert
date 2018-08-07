#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 viewport;
uniform mat4 invProj;
uniform float zNear;
uniform float zFar;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
layout(location = 3) in float inRadius;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec3 outNormalEyeSpace;
layout(location = 2) out vec4 outViewport;
layout(location = 3) out vec3 outPosEyeSpace;
layout(location = 4) out float outRadius;
layout(location = 5) out float outZNear;
layout(location = 6) out float outZFar;
layout(location = 7) out vec3 outNormal;
layout(location = 8) out mat4 outInvProj;

out gl_PerVertex 
{
    vec4 gl_Position;
	float gl_PointSize;
};

void main() 
{
	//Compute position in clip coordinates
	gl_Position = proj * view * model * vec4(inPos,1.0f);	
	
	//Compute and pass the normal in eye space
	outNormalEyeSpace = (view * model * vec4(inNormal, 1.0f)).xyz;
	
	//Compute and pass the position in eye space
	outPosEyeSpace = (view * model * vec4(inPos,1.0f)).xyz;
	
	//Compute the size of the window to be rasterized
	float pointSize = inRadius*proj[1][1]*viewport[3]/(outPosEyeSpace.z);
	
	//Set the size of the window
	gl_PointSize = abs(pointSize);	
	
	//Pass necessary data to fragment shader
	outNormal = inNormal;
	outInvProj = invProj;
	outViewport = viewport;
	outColor = inColor;
	outRadius = inRadius;
	outZNear = zNear;
	outZFar = zFar;
}