#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {

    float alpha = texture(texSampler, fragTexCoord).r;

    if (alpha < 0.5) {
        discard;
    }

    outColor = vec4(fragColor, 1.0);
}