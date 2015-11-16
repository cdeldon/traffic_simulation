//
// Created by Carlo on 18.10.2015.
//
#include <car.h>
#include <road.h>
#include <simulation.h>
#include <common.h>
//#include <math.h>
#include <cmath>


Car::Car(const position pos, Road* const r)
    : p(pos), v(0), road(r)
{
}

Car::Car(const position pos, const velocity vel, Road* const r)
    : p(pos), v(vel), road(r)
{
}

Car::Car( const Car &other)
    : p(other.p), v(other.v), road(other.road)
{
}

Car::Car(const Car &other, Road* const r)
    : p(other.p), v(other.v), road(r)
{
}


// The ODE's right hand side should go here (not complete yet)
Car::acceleration Car::getAcceleration(const double dt, bool & stop_light) const
{
    Settings const * const settings = road->getSimulation()->getSettings();

    // exponent in ODE
    const double delta = 4.f;

    //velocity difference
    const double & deltaV = this->v  -  this->next_car->v;

    //desired gap to leading vehicle
    double s_star = road -> spaceHeadway(this->p)
                    + std::max(0. , this->v * road->timeHeadway(this->p) +
                                   (this->v * deltaV)/(2*std::sqrt(settings->a_max * settings->d_max)));

    // current gap
    double s_alpha = this->next_car->p - this->p;
    if (s_alpha < 0)                // deal with periodic boundary condition
        s_alpha += road->getLength();
    s_alpha -= settings->car_size;

    double gap_term = std::pow(s_star / s_alpha, 2.);
    gap_term = gap_term * (0.2 + 0.8*gap_term);

    // speed limit
    double limit_term = std::pow(v / road->speedLimit(p), delta);


    // traffic light
    double light_decel = -INF;
    std::vector<TrafficLight> l = road->getTrafficLights();
    for (unsigned int i = 0; i < l.size(); ++i)
    {
        if (l[i].pos < this->p || !l[i].isRed(this->road->getSimulation()->getTime()))
            continue;

        //compute required deceleration
        double d = std::abs(v)*v / (l[i].pos - p) / 2;
        if (d<0.5*settings->d_max || d>2 * settings->d_max)
            continue;
        light_decel = std::max(light_decel, d);
    }
    

    return std::min(settings->a_max * (1. - limit_term - gap_term), -light_decel);
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
    Settings const * const settings = road->getSimulation()->getSettings();

    // update the car position
    bool sl(0);
    double a = getAcceleration(dt, sl);


    bool halt = 0;
    std::vector<TrafficLight> l = road->getTrafficLights();
    for (unsigned int i = 0; i < l.size(); ++i)
    {
        if (l[i].isRed(road->getSimulation()->getTime()) && abs(v) < 3 && l[i].pos - 1 < this->p  && l[i].pos > this->p)
        {
            this->v = 0;
            halt = true;
            break;
        }
    }
    if (!halt) {
        double move = this->v * settings->DT + 0.5*a*settings->DT * settings->DT;

        this->v += a * settings->DT;
        this->p += move;
        //this->p += this->v * settings->DT;
    }


    // periodic boundary
    if (this->p > road->getLength())
    {
        this->p -= road->getLength();
        this->road->incThroughput();
    }

}

