#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 viewport;

layout(location = 0) in vec3 inPos;
layout(location = 3) in float inRadius;

out gl_PerVertex 
{
    vec4 gl_Position;
};

void main() 
{
	//Compute position in clip coordinates
	gl_Position = proj * view * model * vec4(inPos,1.0f);
	
	//Compute position in eye coordinates
	vec3 posEyeSpace = (view * model * vec4(inPos,1.0f)).xyz;
	
	//Compute the size of the window to be rasterized
	float pointSize = inRadius*proj[1][1]*viewport[3]/(posEyeSpace.z);
	
	//Decrease the size to avoid issues in steep splats
	gl_PointSize = abs(pointSize)/2.0f;
}