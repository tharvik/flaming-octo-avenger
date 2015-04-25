#include "Plane.hpp"
#include "World.hpp"
#include "Triangle.hpp"

#include "Util.hpp"

#include <iostream>

int main()
{
	// TODO find a better way to unroll throw
	try {
		World world("flaming-octo-avenger");

		Plane plane;

		world.add_object(plane);

		world.main_loop();
	} catch (Util::base_exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
