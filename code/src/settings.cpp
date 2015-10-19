//
// Created by Carlo on 18.10.2015.
//

#include <settings.h>
#include <transform.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <hack.h>

const Settings Settings::predifined = Settings(50.f, 5.f, 1.f, 2.f, 2.5f, 1.f);

Settings::Settings()
{
}

Settings::Settings( const float v, const float dist, const float a, const float dec, const float s, const float t )
        : v_desired(to_ms(v)),
          d_desired(dist),
          a_max(a),
          d_max(dec),
          car_size(s),
          DT(t)
{
    std::cout << "Simulation settings are:\n\n" << toString() << std::endl << std::endl;
}

std::string Settings::toString() const
{
    return "Desired Velocity: \t" + to_string(v_desired) + "\t[m/s]" +
            "\nDesired Distance: \t" + to_string(d_desired) + "\t[m]" +
            "\nMaximum Acceleration:\t" + to_string(a_max) + "\t[m/s^2]" +
            "\nMaximum deceleration:\t" + to_string(d_max) + "\t[m/s^2]" +
            "\nCar Size:\t\t" + to_string(car_size) + "\t[m]" +
            "\nDT:\t\t\t" + to_string(DT) + "\t[s]";

}

/**
 * case where the settings are given directly on the command line
 */
void Settings::readSettings( char **argv )
{
    v_desired = atof(argv[1]);
    d_desired = atof(argv[2]);
    a_max = atof(argv[3]);
    d_max = atof(argv[4]);
    car_size = atof(argv[5]);
    DT = atof(argv[6]);
}

/**
 * case where the settings are passed via settings file
 */
void Settings::readSettings( char *argv)
{
    std::ifstream in(argv);
    if(in.is_open())
    {
        std::string line;
        while( std::getline(in, line))
        {
            //std:: linestream(line);
        }
    }
    else
    {
       // std::cout<<"Error opening settings:\t" << argv << "\n";
       // abort();
    }

    in.close();

}

