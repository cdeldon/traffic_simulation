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
          end_T(T),
          ID("simulation"),
          output_positions(1),
          output_velocities(0),
          output_throughput(1),
          output_freq(1)
{
}

std::string Settings::toString() const
{
    std::string res = std::string("==========================================================\nSimulation settings:\n") +
           "\nID = \"" + ID + "\""
           "\nInitial number of cars:\t" + to_string(n_cars) + "\t[cars]" +
           "\nStreet length:\t\t" + to_string(road_length) + "\t[m]" +
           "\nDesired Velocity: \t" + to_string(v_desired) + "\t[m/s]" +
           "\nDesired Distance: \t" + to_string(d_desired) + "\t[m]" +
           "\nMaximum Acceleration:\t" + to_string(a_max) + "\t[m/s^2]" +
           "\nMaximum deceleration:\t" + to_string(d_max) + "\t[m/s^2]" +
           "\nCar Size:\t\t" + to_string(car_size) + "\t[m]" +
           "\nDT:\t\t\t" + to_string(DT) + "\t[s]" +
           "\nEnd Time:\t\t" + to_string(end_T) + "\t[s]" +
           "\nOutput positions:\t" + to_string(output_positions) +
           "\nOutput velocities:\t" + to_string(output_velocities) +
           "\nOutput throughput:\t" + to_string(output_throughput) +
           "\nWrite output every\t" + to_string(output_freq) + " [DT] = " + to_string(output_freq*DT) + " [s]" +
           "\n==========================================================\n";

    return res;

}


template< typename T >
void Settings::extractFeature( std::string line, std::string feature, T &store )
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

void Settings::extractString(std::string line, std::string feature, std::string &store)
{
    if ( line.find(feature) != std::string::npos )
    {
        std::size_t position = line.find('=');
        if (position == std::string::npos)
            std::cout << "Invalid setting, mising '=': " << line << std::endl;

        store = line.substr(position + 2);
    }
}

void Settings::extractObstacle(const std::string & str)
{
    if (str.find("OBSTACLE") == std::string::npos)
        return;
    Obstacle o;
    std::stringstream ss;
    ss << str.substr(8); //cut off "OBSTACLE"
    ss >> o.start >> o.end >> o.speed_limit >> o.time_headway >> o.space_headway;
    obstacles.push_back(o);
}

void Settings::extractLight(const std::string & str)
{
    if (str.find("LIGHT") == std::string::npos)
        return;
    TrafficLight l;
    std::stringstream ss;
    ss << str.substr(5); // cut off "LIGHT"
    ss >> l.pos >> l.period >> l.duty_cycle;
    traffic_lights.push_back(l);
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
            extractString(line,  "ID", ID);
            extractFeature(line, "POSITIONS", output_positions);
            extractFeature(line, "VELOCITIES", output_velocities);
            extractFeature(line, "THROUGHPUT", output_throughput);
            extractFeature(line, "OUT_FREQ", output_freq);

            extractObstacle(line);
            extractLight(line);
        }
    }
    else
    {
         std::cerr << "Error opening settings:\t" << path << "\n";
        // abort();
    }

    in.close();

}

