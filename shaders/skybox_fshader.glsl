#version 330 core

uniform sampler2D sky;

in vec3 normal;
in vec2 uv;

out vec3 color;

void main()
{
    color = texture(sky, uv).rgb;
}
