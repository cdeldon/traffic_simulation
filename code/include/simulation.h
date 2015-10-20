#ifndef TRAFFIC_SIMULATION_SIMULATION_H
#define TRAFFIC_SIMULATION_SIMULATION_H

#include <road.h>

class Simulation {
public:
    Simulation();
    Simulation(Road &);
    Simulation(Road &, double, double);

private:
    Road road;
    double timeStep;
    double endTime;
    double time;
};

#endif  // TRAFFIC_SIMULATION_SIMULATION_H