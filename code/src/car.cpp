//
// Created by Carlo on 18.10.2015.
//
#include <car.h>
#include <road.h>
#include <simulation.h>
#include <common.h>
#include <math.h>
#include <cmath>


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

    // exponent in ODE
    const double delta = 4.f;

    double deltaV = this->v  -  this->next_car->v;

    double s_star = road -> spaceHeadway(this->p)
                    + std::max(0. , this->v * road->timeHeadway(this->p) +
                                   (this->v*deltaV)/(2*std::sqrt(settings->a_max * settings->d_max)));

    double s_alpha = this->next_car->p - this->p - settings->car_size;

    return std::max(0., settings->a_max * (1. - std::pow(v/road->speedLimit(p), delta) - std::pow(s_star/s_alpha, 2.)));
}

std::string Car::toString() const
{
    return to_string(p);
}


unsigned int Car::index() const
{
    return road->find(this);
}

void Car::update_postion(const double dt)
{
    // The ODE's right hand side should go here (not complete yet)
    Settings const * const settings = road->getSimulation()->getSettings();

    // update the car position with a symplectic integration
    this -> v += getAcceleration() * settings->DT;
    this -> p += this -> v * settings->DT;
}

