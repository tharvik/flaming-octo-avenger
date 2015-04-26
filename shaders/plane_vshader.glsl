#version 330 core

uniform mat4 mvp;
uniform sampler2D pattern;

in vec2 position;

out vec2 uv;

void main() {
    uv = (position + vec2(1.0, 1.0)) * 0.5;

    // Convert the 2D position into 3D positions that all lay in a horizontal
    // plane.
    // TODO 6: Animate the height of the grid points as a sine function of the
    // 'time' and the position ('uv') within the grid.
    //float height = 0.0;
    float height = texture(pattern, uv).x;
    vec3 pos_3d = vec3(position.x, height, -position.y);

    gl_Position = mvp * vec4(pos_3d, 1.0);

    //vcolor = vec3(height,0,0);
    //vcolor = texture(pattern, uv / 4).rgb;
    //vcolor = vec3(texture(pattern, uv).y,0,0);

    /*vec2 uv2 = -uv;

      float time = 3.1415;

      float s = sin(time);
      float c = cos(time);

      float height = texture(pattern, uv)[0] - 0.5;
      height *= - s * s / 5;

      float height2 = texture(pattern, uv2)[0] - 0.5;
      height2 *= - c * c / 5;

      height += height2;

      height *= 10;

      vec3 pos_3d = vec3(position.x, height, -position.y);
      gl_Position = mvp * vec4(pos_3d, 1.0);*/
}
