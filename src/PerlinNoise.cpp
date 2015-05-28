#include "PerlinNoise.hpp"

#include "Plane.hpp"

#include <algorithm>

#include <iostream>

#include <math.h>

/**
 * @todo remove deps on libnoise
 * @todo use Fractional Brownian motion
 */
PerlinNoise::PerlinNoise(size_t const size)
	: framebuffer(size)
{
	std::set<Uniform> uniforms;
	std::set<Attribute> attributes;
	std::set<Texture> textures;

	std::vector<uint32_t> data;
	data.reserve(size * size);

	/*double const x_base = 0.5;
	double const y_base = 0.1;
	double const x_end = 1.6;
	double const y_end = 1.1;
	double const ground = 0.5;*/

	double const x_base = 1.5;
	double const y_base = 1.1;
	double const x_end = 10.6;
	double const y_end = 10.1;
	double const ground = 1.5;

	for (double x = x_base; x < x_end; x += (x_end - x_base) / size) {
		for (double y = y_base; y < y_end; y += (y_end - y_base) / size) {
			double value = 0.0;

			// Get the coherent-noise value from the input value and add it to the
			// final result.
			value = generateNoise (x, ground, y);

			if (value < 0)
				value = 0;
			value = value / 7;
			data.push_back(value * 0xFF);
		}
	}

	textures.emplace("noise", data);

	Plane plane("perlin_noise", uniforms, attributes, textures);

	//program.bind();
	framebuffer.bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	plane.draw();

	framebuffer.unbind();
	//program.unbind();
}

//Adapted from the source code found in libnoise
double PerlinNoise::generateNoise (double x, double y, double z)
{
  // Create a unit-length cube aligned along an integer boundary.  This cube
  // surrounds the input point.
  int x0 = (x > 0.0? (int)x: (int)x - 1);
  int x1 = x0 + 1;
  int y0 = (y > 0.0? (int)y: (int)y - 1);
  int y1 = y0 + 1;
  int z0 = (z > 0.0? (int)z: (int)z - 1);
  int z1 = z0 + 1;

  // Map the difference between the coordinates of the input value and the
  // coordinates of the cube's outer-lower-left vertex onto an S-curve.
  double xs = 0, ys = 0, zs = 0, a, a3, a4, a5;
  
  a = x - (double)x0;
  a3 = a * a * a;
  a4 = a3 * a;
  a5 = a4 * a;
  xs = (6.0 * a5) - (15.0 * a4) + (10.0 * a3);

  a = y - (double)y0;
  a3 = a * a * a;
  a4 = a3 * a;
  a5 = a4 * a;
  ys = (6.0 * a5) - (15.0 * a4) + (10.0 * a3);
  
  a = z - (double)z0;
  a3 = a * a * a;
  a4 = a3 * a;
  a5 = a4 * a;
  zs = (6.0 * a5) - (15.0 * a4) + (10.0 * a3);

  // Now calculate the noise values at each vertex of the cube.  To generate
  // the coherent-noise value at the input point, interpolate these eight
  // noise values using the S-curve value as the interpolant (trilinear
  // interpolation.)
  double n0, n1, ix0, ix1, iy0, iy1;
  n0   = GradientNoise (x, y, z, x0, y0, z0);
  n1   = GradientNoise (x, y, z, x1, y0, z0);
  ix0  = ((1.0 - xs) * n0) + (xs * n1);
  n0   = GradientNoise (x, y, z, x0, y1, z0);
  n1   = GradientNoise (x, y, z, x1, y1, z0);
  ix1  = ((1.0 - xs) * n0) + (xs * n1);
  iy0  = ((1.0 - ys) * ix0) + (ys * ix1);;
  n0   = GradientNoise (x, y, z, x0, y0, z1);
  n1   = GradientNoise (x, y, z, x1, y0, z1);
  ix0  = ((1.0 - xs) * n0) + (xs * n1);
  n0   = GradientNoise (x, y, z, x0, y1, z1);
  n1   = GradientNoise (x, y, z, x1, y1, z1);
  ix1  = ((1.0 - xs) * n0) + (xs * n1);
  iy1  = ((1.0 - ys) * ix0) + (ys * ix1);
  
  return ((1.0 - zs) * iy0) + (zs * iy1);
}

double PerlinNoise::GradientNoise (double fx, double fy, double fz, int ix,
  int iy, int iz)
{
  // Randomly generate a gradient vector given the integer coordinates of the
  // input value.  This implementation generates a random number and uses it
  // as an index into a normalized-vector lookup table.
  int vectorIndex = (
      1619     * ix
    + 31337    * iy
    + 6971     * iz
    + 1013     )
    & 0xffffffff;
  vectorIndex ^= (vectorIndex >> 8);
  vectorIndex &= 0xff;

  double xvGradient = g_randomVectors[(vectorIndex << 2)    ];
  double yvGradient = g_randomVectors[(vectorIndex << 2) + 1];
  double zvGradient = g_randomVectors[(vectorIndex << 2) + 2];

  // Set up us another vector equal to the distance between the two vectors
  // passed to this function.
  double xvPoint = (fx - (double)ix);
  double yvPoint = (fy - (double)iy);
  double zvPoint = (fz - (double)iz);

  // Now compute the dot product of the gradient vector with the distance
  // vector.  The resulting value is gradient noise.  Apply a scaling value
  // so that this noise value ranges from -1.0 to 1.0.
  return ((xvGradient * xvPoint)
    + (yvGradient * yvPoint)
    + (zvGradient * zvPoint)) * 2.12;
}

Texture PerlinNoise::get_texture(std::string const name) const
{
	return Texture(name, 0, framebuffer.color_attachement);
}
