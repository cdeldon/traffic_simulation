#include <simulation.h>

Simulation::Simulation()
    : timeStep(0), endTime(0), time(0)
{
}

Simulation::Simulation(Road & r)
    : road(r), timeStep(0), endTime(0), time(0)
{
}

Simulation::Simulation(Road & r, double dt, double T)
    : road(r), timeStep(dt), endTime(T)
{
}
