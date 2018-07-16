#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 viewport;
uniform mat4 invProj;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec3 outNormalEyeSpace;
layout(location = 2) out vec4 outViewport;
layout(location = 3) out vec3 outPosEyeSpace;
layout(location = 4) out mat4 outInvProj;

out gl_PerVertex 
{
    vec4 gl_Position;
};

void main() 
{
	gl_Position = proj * view * model * vec4(inPos,1.0f);

	outColor = inColor;
}