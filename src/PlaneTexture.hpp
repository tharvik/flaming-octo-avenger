#ifndef PLANETEXTURE_HPP
#define PLANETEXTURE_HPP

#include "Plane.hpp"

class PlaneTexture : public Plane {
	public:
		PlaneTexture(size_t const size = 512);

	private:
		static std::set<Texture> get_texture(size_t const size);
};

#endif
