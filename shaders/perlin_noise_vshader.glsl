#version 330 core

in vec2 position;

out vec2 uv;
out vec3 vcolor;

void main() {
    uv = (position + vec2(1.0, 1.0)) * 0.5;

    vec3 pos_3d = vec3(position.x, 0, -position.y);

    gl_Position = vec4(position.x, position.y, 0, 1);

    vcolor = vec3((position.x + 1) / 2.0, 0, 0);
}
