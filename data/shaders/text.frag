#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

// TODO: Investigate differences in these methods
#define USE_LITTLE

layout(binding = 0) uniform UniformObject {
	mat4 modelView;
	float alpha;

	vec4 colour;
	float scale;
} object;

layout(binding = 2) uniform sampler2DArray samplerMsdf;

layout(location = 0) in vec3 inUV;

layout(location = 0) out vec4 outColour;

float median(float r, float g, float b) {
	return max(min(r, g), min(max(r, g), b));
}

void main() {
#ifdef USE_LITTLE
    vec3 msdfSample = texture(samplerMsdf, inUV).rgb;
	float dist = (median(msdfSample.r, msdfSample.g, msdfSample.b) - 0.5f);
	float o = clamp(dist + 0.5f, 0.0f, 1.0f);
	outColour = object.colour;
	outColour.a *= o* object.alpha;
#else	
    vec2 pos = inUV.xy;
    vec3 msdfSample = texture(samplerMsdf, inUV).rgb;
    ivec2 sz = textureSize(samplerMsdf, 0).xy;
    float dx = dFdx(pos.x) * sz.x; 
    float dy = dFdy(pos.y) * sz.y;
    float toPixels = 8.0 * inversesqrt(dx * dx + dy * dy);
    float sigDist = median(msdfSample.r, msdfSample.g, msdfSample.b);
    float w = fwidth(sigDist);
    float opacity = smoothstep(0.5 - w, 0.5 + w, sigDist);    
    outColour = vec4(object.colour.rgb, opacity * object.alpha);
#endif

	if (outColour.a < 0.1f) {
		outColour = vec4(0.0f);
		discard;
	}
}
