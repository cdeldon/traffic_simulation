#include <iostream>
#include <vector>

#include <simulation.h>


#if defined(_MSC_VER) 
	std::string outDir = "../output/";
#else
	std::string outDir = "../../output/";
#endif

Simulation * active_simulation;

int main( int argc, char **argv )
{

    active_simulation = new Simulation();
    active_simulation->loadDefaultSettings();
    if ( argc == 1 )
    {
        std::cout << "Loaded predefined settings:" << std::endl;
    }
    else if ( argc == 2 )
    {
		std::cout << "Loaded settings from argv[1]:" << std::endl;
        active_simulation->readSettings(argv[1]);
    }

    std::cout << active_simulation->getSettings()->toString();

    active_simulation -> run();

    // TODO add time stamp to the path
    active_simulation->getRoad()->writePositions((outDir + active_simulation->getSettings()->ID + ".dat").c_str());
    std::cout<<(outDir + active_simulation->getSettings()->ID + ".dat");

    std::cout << "Execution completed\n";

    return 1;
}