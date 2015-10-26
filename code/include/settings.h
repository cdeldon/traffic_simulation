//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_SETTINGS_H
#define TRAFFIC_SIMULATION_SETTINGS_H

#include <string>

struct Settings
{
    unsigned int n_cars;
    double road_length;

    double v_desired;
    double d_desired;
    double a_max;
    double d_max;
    double car_size;

    double DT;
    double end_T;

    //TODO output settings and flags
    std::string ID;

    /**
     * Default settings
     */
    static const Settings predefined;

    Settings();

    Settings( const unsigned int n, const double m, const double v, const double dist, const double a, const double dec,
              const double s, const double dt, const double T);

    std::string toString() const;

    void readSettings(const char *path);
};


#endif //TRAFFIC_SIMULATION_SETTINGS_H
