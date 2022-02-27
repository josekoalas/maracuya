#version 450

layout(binding = 0) uniform UniformBuffer {
    float time;
} ubo;

layout(location = 0) in vec2 in_pos;

layout(location = 0) out vec2 uv;
layout(location = 1) out float time;

void main() {
    gl_Position = vec4(in_pos, 0.0, 1.0);
    uv = in_pos;
    time = ubo.time;
}
