//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_SETTINGS_H
#define TRAFFIC_SIMULATION_SETTINGS_H

#include <string>
#include <vector>
#include <road.h>

struct Settings
{
    unsigned int n_cars;
    double road_length;

    double filling;

    double v_desired;
    double d_desired;
    double t_desired;
    double a_max;
    double d_max;
    double car_size;

    double DT;
    double end_T;


    //TODO output settings and flags
    std::string ID;
    bool output_positions;
    bool output_velocities;
    bool output_throughput;
    int output_freq;

    std::vector<Obstacle> obstacles;
    std::vector<TrafficLight> traffic_lights;

    /**
     * Default settings
     */
    static const Settings predefined;

    Settings();

    Settings( const unsigned int n, const double m, const double v, const double dist, const double a, const double dec,
              const double s, const double dt, const double T);

    std::string toString() const;

    void readSettings(const char *path);

private:
    template< typename T > void extractFeature(std::string line, std::string feature, T &store);
    void extractString(std::string line, std::string feature, std::string &store);
    void extractObstacle(const std::string &);
    void extractLight(const std::string &);
};


#endif //TRAFFIC_SIMULATION_SETTINGS_H
