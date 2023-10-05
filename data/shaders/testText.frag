#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 internalColor;
layout(location = 1) in vec3 outlineColor;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

//void main() {
//
//    float alpha = texture(texSampler, fragTexCoord).r;
//
//    if (alpha < 0.5) {
//        discard;
//    }
//
//    outColor = vec4(fragColor, 1.0);
//}

const float smoothing = 1.0/16.0;
const float outlineWidth = 2.0/16.0;
const float outerEdgeCenter = 0.5 - outlineWidth;

void main() {
    float distance = texture(texSampler, fragTexCoord).r;
    float alpha = smoothstep(outerEdgeCenter - smoothing, outerEdgeCenter + smoothing, distance);
    float border = smoothstep(0.5 - smoothing, 0.5 + smoothing, distance);
    outColor = vec4( mix(outlineColor.rgb, internalColor.rgb, border), alpha );
}