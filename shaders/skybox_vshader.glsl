#version 330 core

uniform mat4 mvp;

in vec3 vpoint;

out vec2 uv;

void main() {
	uv = (vpoint.xy);
	
	gl_Position = mvp * vec4(vpoint, 1.0);
}
