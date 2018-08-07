#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 viewport;

layout(location = 0) in vec3 inPos;

out gl_PerVertex 
{
    vec4 gl_Position;
};

void main() 
{
	//Compute position in clip coordinates
	gl_Position = proj * view * model * vec4(inPos,1.0f);
}