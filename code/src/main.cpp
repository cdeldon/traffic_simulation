#include <iostream>
#include <vector>
#include <road.h>
#include <settings.h>
#include <common.h>

Settings settings;
#if defined(_MSC_VER) 
	std::string outDir = "../output/";
#else
	std::string outDir = "../../output/";
#endif

int main( int argc, char **argv )
{
    if ( argc == 1 )
    {
        std::cout << "Loaded predefined settings:" << std::endl;
        settings = Settings::predefined;
    }
    else if ( argc == 2 )
    {
		std::cout << "Loaded settings from argv[1]:" << std::endl;
        settings.readSettings(argv[1]);
    }

    std::cout << settings.toString();

    std::vector<double> pos(10, 0.4f);
    Road road(pos);

    road.write(( outDir + "Car_position.dat" ).c_str());
    std::cout << "Files have been written\n";

    return 1;
}