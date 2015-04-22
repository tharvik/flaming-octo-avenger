#version 330 core
out vec3 color;
in vec2 uv;
uniform sampler2D pattern;

void main() {
    color = texture(pattern, uv).rgb;
}
