#version 330 core

uniform mat4 mvp;

in vec3 vpoint;

void main() {
	//uv = (position + vec2(1.0, 1.0)) * 0.5;

	gl_Position = mvp * vec4(vpoint, 1.0);
}
