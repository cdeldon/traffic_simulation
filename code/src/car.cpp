//
// Created by Carlo on 18.10.2015.
//
#include <car.h>
#include <road.h>
#include <simulation.h>
#include <common.h>
#include <math.h>


Car::Car(const position pos, const Road* const r)
    : p(pos), v(0), road(r)
{
}

Car::Car(const position pos, const velocity vel, const Road* const r)
    : p(pos), v(vel), road(r)
{
}

Car::Car( const Car &other)
    : p(other.p), v(other.v), road(other.road)
{
}

Car::Car(const Car &other, const Road* const r)
    : p(other.p), v(other.v), road(r)
{
}

Car::acceleration Car::getAcceleration() const
{
    // The ODE's right hand side should go here (not complete yet)
    Settings const * const settings = road->getSimulation()->getSettings();

    return settings -> a_max * (1 - pow(v/road->speedLimit(p), 4));
}

std::string Car::toString() const
{
    return to_string(p);
}


unsigned int Car::index() const
{
    return road->find(this);
}

