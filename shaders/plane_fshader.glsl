#version 330 core

uniform sampler2D tex;

in vec2 uv;
in vec3 vcolor;

out vec3 color;

void main() {
    color = texture(tex, uv).rgb;
    color = vcolor;
}
