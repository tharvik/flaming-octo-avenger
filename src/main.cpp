#include "Plane.hpp"
#include "World.hpp"
#include "Triangle.hpp"

#include "Util.hpp"

#include <iostream>

/**
 * @todo find a better way to unroll throw
 */
int main()
{
	try {
		World world("flaming-octo-avenger");

		Plane plane;

		world.add_object(plane);

		world.main_loop();
	} catch (Util::base_exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (std::string& e) {
		std::cerr << e << std::endl;
	}
}
