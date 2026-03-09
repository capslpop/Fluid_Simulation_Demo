#shader VERTEX
#version 410 core

layout(std140) uniform matrix_uniforms {
    mat4 projection;
    mat4 view;
    mat4 model;
};

layout(location = 0) in vec3 position;

void main() {
    gl_PointSize = 20.0;
    gl_Position = projection * view * model * vec4(position, 1.0);
}

#shader FRAGMENT
#version 410 core

out vec4 frag_color;

void main() {
    frag_color = vec4(1.0, 0.0, 0.0, 1.0);
}