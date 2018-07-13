#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec3 outNormalEyeSpace;

out gl_PerVertex 
{
    vec4 gl_Position;
};

void main() 
{
	gl_Position = proj * view * model * vec4(inPos,1.0f);
	outColor = inColor;
	outNormalEyeSpace = (view * vec4(inNormal, 1.0f)).xyz;
}