#version 330 core

uniform sampler2D grass;
uniform sampler2D rock;
uniform sampler2D sand;
uniform sampler2D snow;

in vec3 normal;
in vec2 uv;
in float height;

out vec3 color;

vec3 ground = vec3(0,-1,0);
float min_rock = 0.5;

float min_max(float min, float max, float val)
{
	float res = (val - min) / (max - min);

	return clamp(res, 0, 1);
}

float alpha1()
{
	float res = dot(ground, normal);

	return min_max(1 - min_rock, 1, res);
}

float alpha2()
{
	float res = 1 - dot(ground, normal);

	return min_max(min_rock, 1, res) * 2;
}

float alpha3()
{
	return 1 - min_max(0.0, 0.1, height);
}

float alpha4()
{
	return min_max(0.4, 0.8, height) * 3;
}

void main()
{
	vec3 light = normalize(vec3(1,1,1));

	color = vec3(0,0,0);

	float alpha[4];

	alpha[0] = alpha1();
	alpha[1] = alpha2();
	alpha[2] = alpha3();
	alpha[3] = alpha4();

	color += alpha[0] * texture(grass, uv * 10).xyz;
	color += alpha[1] * texture(rock, uv * 10).xyz;
	color += alpha[2] * texture(sand, uv * 60).xyz;
	color += alpha[3] * texture(snow, uv * 30).xyz;

	color /= 4;

	if (height == 0)
		color = vec3(14./255, 61./255, 109./255);

	float aver = dot(light, normal);
	color = mix(color, vec3(0,0,0), aver);
}
