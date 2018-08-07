#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 viewport;
uniform mat4 lightView;
uniform mat4 lightProj;

layout(location = 0) in vec3 inPos;
layout(location = 3) in float inRadius;

out gl_PerVertex 
{
    vec4 gl_Position;
};

void main() 
{
	//Compute position in clip coordinates
	gl_Position = lightProj * lightView * model* vec4(inPos,1.0f);
	
	gl_PointSize = 5.0f;
}