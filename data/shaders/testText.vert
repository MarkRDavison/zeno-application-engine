#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

layout(push_constant) uniform PushConstantObject {
	mat4 model;
    vec4 internalColor;
    vec4 outlineColor;
} object;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec3 internalColor;
layout(location = 1) out vec3 outlineColor;
layout(location = 2) out vec2 fragTexCoord;

void main() {
    gl_Position = ubo.proj * ubo.view * object.model * vec4(inPosition, 1.0);
    internalColor = object.internalColor.rgb;
    outlineColor = object.outlineColor.rgb;
    fragTexCoord = inTexCoord;
}