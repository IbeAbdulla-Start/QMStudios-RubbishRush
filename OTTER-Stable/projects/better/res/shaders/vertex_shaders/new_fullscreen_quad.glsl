#version 440

layout (location = 0) in vec2 inPos;

layout (location = 0) out vec2 outUV;
layout (location = 1) out vec3 outViewDir;

#include "../fragments/frame_uniforms.glsl"
noperspective out vec2 vTexcoord;

void main() {
    mat4 clipToView = inverse(u_Projection);

    vTexcoord = inPos *0.5+0.5;
    gl_Position = vec4(inPos, 0, 1);
    outUV = (inPos + 1) / 2;
    outViewDir = (clipToView * vec4(inPos, 0, 1)).xyz;
}