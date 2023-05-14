#version 450
#extension GL_ARB_separate_shader_objects:enable

<<<<<<< HEAD
layout(location = 0) out vec4 outColor;
layout(location = 0) in vec3 color;

void main() {
    outColor = vec4(color, 1.0);
=======
layout(location = 0) in vec4 fragColor;
layout(location = 0) out vec4 outColor;

void main() {
    outColor = fragColor;
>>>>>>> parent of 0311774... Delete shader.frag
}