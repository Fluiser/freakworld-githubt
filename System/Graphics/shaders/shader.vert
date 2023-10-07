#version 450
#extension GL_ARB_separate_shader_objects:enable

layout(location = 0) out vec3 fragColor;

layout(location = 0) in vec2 positions;
layout(location = 1) in vec3 colors;

void main() {
    gl_Position = vec4(positions, 0.0, 1.0);
    fragColor = colors;
}