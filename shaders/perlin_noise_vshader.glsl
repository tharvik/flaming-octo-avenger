#version 330 core

uniform sampler2D noise;

in vec2 position;

out vec2 uv;
out vec3 vcolor;

void main() {
    uv = (position + vec2(1.0, 1.0)) * 0.5;

    gl_Position = vec4(position.x, position.y, 0, 1);

    float height = texture(noise, uv).x;
    vcolor = vec3(height, height, height);
}
