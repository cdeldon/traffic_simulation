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

const Settings Settings::predefined = Settings(1e5, 1e5f, 50.f, 5.f, 1.f, 2.f, 2.5f, 1.f, 40*60);

Settings::Settings()
{
}

Settings::Settings( const unsigned int n, const double m, const double v, const double dist, const double a,
                    const double dec, const double s, const double dt , const double T)
        : n_cars(n),
          road_length(m),
          v_desired(to_ms(v)),
          d_desired(dist),
          a_max(a),
          d_max(dec),
          car_size(s),
          DT(dt),
          end_T(T)
{
}

std::string Settings::toString() const
{
    return "Simulation settings:\n\nNumber of cars:\t\t" + to_string(n_cars) + "\t[cars]" +
           "\nStreet length:\t\t" + to_string(road_length) + "\t[m]" +
           "\nDesired Velocity: \t" + to_string(v_desired) + "\t[m/s]" +
           "\nDesired Distance: \t" + to_string(d_desired) + "\t[m]" +
           "\nMaximum Acceleration:\t" + to_string(a_max) + "\t[m/s^2]" +
           "\nMaximum deceleration:\t" + to_string(d_max) + "\t[m/s^2]" +
           "\nCar Size:\t\t" + to_string(car_size) + "\t[m]" +
           "\nDT:\t\t\t" + to_string(DT) + "\t[s]" +
           "\nEnd Time:\t\t" + to_string(end_T) + "\t[s]\n\n";

    //TODO complete with new settings parameters

}


template< typename T >
void extractFeature( std::string line, std::string feature, T &store )
{
    if ( line.find(feature) != std::string::npos )
    {
        std::size_t position = line.find('=');
        if (position == std::string::npos)
            std::cout << "Invalid setting, mising '=': " << line << std::endl;

        std::string stringFeature = line.substr(position + 1);

        store = strtod(stringFeature.c_str(), 0);
    }
}

void extractString( std::string line, std::string feature, std::string &store )
{
    if ( line.find(feature) != std::string::npos )
    {
        std::size_t position = line.find('=');
        if (position == std::string::npos)
            std::cout << "Invalid setting, mising '=': " << line << std::endl;

        store = line.substr(position + 2);
    }
}

/**
 * case where the settings are passed via settings file
 */
void Settings::readSettings( const char *path )
{
    std::ifstream in(path);
    if ( in.is_open())
    {
        std::string line;
        while ( std::getline(in, line))
        {
            extractFeature(line, "N_CARS", n_cars);
            extractFeature(line, "ROAD_LENGTH", road_length);
            extractFeature(line, "VMAX", v_desired);
            extractFeature(line, "MIN_DIST", d_desired);
            extractFeature(line, "AMAX", a_max);
            extractFeature(line, "DMAX", d_max);
            extractFeature(line, "CAR_SIZE", car_size);
            extractFeature(line, "DT", DT);
            extractFeature(line, "END_TIME", end_T);
            extractString(line, "ID", ID);
        }
    }
    else
    {
         std::cerr << "Error opening settings:\t" << path << "\n";
        // abort();
    }

    in.close();

}

