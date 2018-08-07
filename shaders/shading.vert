#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 viewport;
uniform mat4 invProj;
uniform float zNear;
uniform float zFar;

uniform vec3 lightPos;
uniform mat4 lightView;
uniform mat4 lightProj;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float specularPower;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
layout(location = 3) in float inRadius;

layout(location = 0) out vec3 outPos;
layout(location = 1) out vec4 outPosLightSpace;
layout(location = 2) out vec3 outLightPos;
layout(location = 3) out vec3 outAmbient;
layout(location = 4) out vec3 outDiffuse;
layout(location = 5) out vec3 outSpecular;
layout(location = 6) out float outSpecularPower;
layout(location = 7) out mat4 outViewModel;

out gl_PerVertex 
{
    vec4 gl_Position;
	float gl_PointSize;
};

void main() 
{
	//Compute position in clip coordinates
	gl_Position = proj * view * model * vec4(inPos,1.0f);
	
	//Compute position in light space
	outPosLightSpace = lightProj * lightView * model* vec4(inPos,1.0f);
	
	//Change NDC coords to 0 to 1 range
	outPosLightSpace = 0.5f*outPosLightSpace+0.5f;
	
	//Change the x and y NDC coords to window coords for shadow map lookup
	outPosLightSpace.x *= viewport[2];
	outPosLightSpace.y *= viewport[3];	
	
	//Compute position in eye coordinates
	vec3 posEyeSpace = (view * model * vec4(inPos,1.0f)).xyz;
	
	//Compute the size of the window to be rasterized
	float pointSize = inRadius*proj[1][1]*viewport[3]/(posEyeSpace.z);
	
	//Set the size of the window
	gl_PointSize = abs(pointSize);	

	//Pass necessary data to fragment shader
	outViewModel = view*model;
	outPos = inPos;
	outLightPos = (view*vec4(lightPos, 1.0f)).xyz;
	outAmbient = ambient;
	outDiffuse = diffuse;
	outSpecular = specular;
	outSpecularPower = specularPower;
	
	
	
}