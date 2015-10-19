//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_SETTINGS_H
#define TRAFFIC_SIMULATION_SETTINGS_H

#include <string>

struct Settings
{
    float v_desired;
    float d_desired;
    float a_max;
    float d_max;
    float car_size;

    float DT;

    /**
     * Default settings
     */
    static const Settings predifined;

    Settings();

    Settings( const float v, const float dist, const float a, const float dec, const float s, const float t );

    std::string toString() const;

    void readSettings( char **argv );
    void readSettings( char *argv);
};


#endif //TRAFFIC_SIMULATION_SETTINGS_H
