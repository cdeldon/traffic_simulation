#include <iostream>
#include <vector>
#include <common.h>
#include <simulation.h>


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
		std::cout << "Loading settings from argv[1]..." << std::endl;
        active_simulation->readSettings(argv[1]);
    }

    std::cout << active_simulation->getSettings()->toString();

    active_simulation -> run();

    std::cout << "Execution completed\n";

    return 0;
}