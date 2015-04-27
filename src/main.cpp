#include "Mountain.hpp"
#include "World.hpp"

#include "Util.hpp"

#include <iostream>

/**
 * @todo find a better way to unroll throw
 */
int main()
{
	try {
		World world("flaming-octo-avenger");

		Mountain mountain;

		world.add_object(mountain);

		world.main_loop();
	} catch (Util::base_exception& e) {
		std::cerr << e.what() << std::endl;
	} catch (std::string& e) {
		std::cerr << e << std::endl;
	}
}
