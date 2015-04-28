#version 330 core

uniform mat4 mvp;
uniform sampler2D pattern;

in vec2 position;

out vec2 uv;
out vec3 vcolor;

vec3 get_normal(vec2 uv) {
	float height = texture(pattern, uv).x;
	float step = 1 / 512.f;


	//calculate the neigbour positions
	vec4 prev_x = vec4(uv.x, 0.0, uv.y, 1.0);
	vec4 prev_z = vec4(uv.x, 0.0, uv.y, 1.0);
	vec4 next_x = vec4(uv.x, 0.0, uv.y, 1.0);
	vec4 next_z = vec4(uv.x, 0.0, uv.y, 1.0);
	prev_x.x -= step;    prev_z.z -= step;
	next_x.x += step;    next_z.z += step;
	//calculate neighbour heights / positions, with scaling
	vec4 q;
	q = texture2D(pattern, prev_x.xz); prev_x.y = ( (q.x + q.y + q.z) / 3.0 );
	q = texture2D(pattern, next_x.xz); next_x.y = ( (q.x + q.y + q.z) / 3.0 );
	q = texture2D(pattern, prev_z.xz); prev_z.y = ( (q.x + q.y + q.z) / 3.0 );
	q = texture2D(pattern, next_z.xz); next_z.y = ( (q.x + q.y + q.z) / 3.0 );

	// we now have four neighbouring vertices, positions calculated. Now we need a normal.
	vec3 tangent = (next_x - prev_x).xyz;
	vec3 bitangent = (next_z - prev_z).xyz;
	vec3 normal = normalize( cross(tangent, bitangent) );

	return normal;
}

void main() {
	uv = (position + vec2(1.0, 1.0)) * 0.5;

	float height = texture(pattern, uv).x;
	vec3 pos_3d = vec3(position.x, height, -position.y);
	gl_Position = mvp * vec4(pos_3d, 1.0);

	vec3 light = normalize(vec3(1,1,1));
	vec3 normal = get_normal(uv);
	float aver = dot(light, normal);

	if (height > 0.8)
		vcolor = vec3(1,1,1);
	else if (height > 0.5)
		vcolor = vec3(0,1,0);
	else
		vcolor = vec3(1,0.5,0);

	vcolor = normalize(vcolor);
	vcolor = mix(vcolor, vec3(0,0,0), aver);
}
