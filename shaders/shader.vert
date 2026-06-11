#version 450 // Use GLSL 4.5

layout(location = 0) in vec3 pos; // Output color for vertex (location is required)
layout(location = 1) in vec3 col;
layout(location = 2) in vec2 uv;

layout (std140, set = 0, binding = 0) uniform UboModelViewProjection {
	mat4 model;
	mat4 view;
	mat4 projection;
} uboModelViewProjection;

layout(location = 0) out vec3 fragCol;
layout(location = 1) out vec2 fragUv;

void main() 
{
	gl_Position = uboModelViewProjection.projection * uboModelViewProjection.view * uboModelViewProjection.model * vec4(pos, 1.0);
	fragCol = col;
	fragUv = uv;
}