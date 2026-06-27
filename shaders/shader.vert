#version 450 // Use GLSL 4.5

// Per-vertex data (binding 0)
layout(location = 0) in vec3 pos; // per-vertex: unit quad position in [-1, 1]
layout(location = 1) in vec2 uv;  // per-vertex: uv coordinates [0, 1]

// Per-instance data (binding 1)
layout(location = 2) in vec4 inRect;  // xy = center pos (NDC), zw = half-size (NDC)
layout(location = 3) in vec4 inColor; // RGBA

layout (std140, set = 0, binding = 0) uniform UboModelViewProjection {
	mat4 model;
	mat4 view;
	mat4 projection;
} uboModelViewProjection;


layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragUv;

void main() 
{
	// Place ther shared unit quad at this instance's rectangle
	vec2 worldPos = pos.xy * inRect.zw + inRect.xy;
	gl_Position = uboModelViewProjection.projection * uboModelViewProjection.view * uboModelViewProjection.model * vec4(worldPos, 0.0, 1.0);
	fragColor = inColor;
	fragUv = uv;
}