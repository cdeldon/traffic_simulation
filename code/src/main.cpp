#include <iostream>
#include <vector>
#include <road.h>
#include <settings.h>
#include <common.h>

Settings settings;

std::string outDir = "../../output/";

int main( int argc, char **argv )
{
    if ( argc == 1 )
    {
        settings = Settings::predifined;
    }
    else if ( argc == 2 )
    {
        settings.readSettings(argv[1]);
    }
    else
    {
        settings.readSettings(argv);
    }

    std::vector<float> pos(10, 0.4f);
    Road road(pos);

    road.write(( outDir + "Car_position.dat" ).c_str());
    std::cout << "Files have been written\n";

    return 1;
}