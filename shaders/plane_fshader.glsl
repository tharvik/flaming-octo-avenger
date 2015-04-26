#version 330 core
in vec3 vcolor;
out vec3 color;
in vec2 uv;
uniform sampler2D pattern;

void main() {
    color = texture(pattern, uv).rgb;
    //color = vcolor;
}
