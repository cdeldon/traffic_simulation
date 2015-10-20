//
// Created by Carlo on 18.10.2015.
//
#include <car.h>
#include <common.h>


Car::Car(const position pos)
    : p(pos), v(0)
{
}

Car::Car(const double pos, const velocity vel)
    : p(pos), v(vel)
{
}

Car::Car( const Car &other )
    : p(other.p), v(other.v), nextCar(other.nextCar), prevCar(other.prevCar)
{
}

std::string Car::toString() const
{
    return to_string(p);
}

