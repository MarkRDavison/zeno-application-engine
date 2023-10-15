#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(binding = 0) uniform UniformBufferObject {
	mat4 modelView;
	float alpha;
	float scale;
    
	vec4 internalColor;
	vec4 outlineColor;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec3 internalColor;
layout(location = 1) out vec3 outlineColor;
layout(location = 2) out vec2 fragTexCoord;

void main() {
    gl_Position = ubo.modelView * vec4(inPosition.x * ubo.scale, inPosition.y * ubo.scale, inPosition.z, 1.0);
    internalColor = ubo.internalColor.rgb;
    outlineColor = ubo.outlineColor.rgb;
    fragTexCoord = inTexCoord;
}