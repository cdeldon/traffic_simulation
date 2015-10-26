#include <iostream>
#include <vector>

#include <simulation.h>
#include <common.h>





#if defined(_MSC_VER) 
	std::string outDir = "../output/";
#else
	std::string outDir = "../../output/";
#endif

Simulation * active_simulation;

int main( int argc, char **argv )
{

    active_simulation = new Simulation();

    if ( argc == 1 )
    {
        std::cout << "Loaded predefined settings:" << std::endl;
        active_simulation->loadDefaultSettings();
    }
    else if ( argc == 2 )
    {
		std::cout << "Loaded settings from argv[1]:" << std::endl;
        active_simulation->readSettings(argv[1]);
    }

    std::cout << active_simulation->getSettings()->toString();

    active_simulation -> run();

    // TODO add time stamp to the path
    active_simulation->getRoad()->writePositions((outDir + "Car_position.dat").c_str());

    std::cout << "Execution completed\n";

    return 1;
}