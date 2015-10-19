//
// Created by Carlo on 18.10.2015.
//
#include <car.h>
#include <common.h>

const Car::velocity Car::V_DESIRED = settings.v_desired;
const Car::position Car::DIST_DESIRED = settings.d_desired;
const Car::acceleration Car::A_MAX = settings.a_max;
const Car::acceleration Car::D_MAX = settings.d_desired;
const Car::dimension Car::LENGTH = settings.car_size;

Car::Car( const float pos, const unsigned int i )
        : idx(i),
          p(pos)
{
}

Car::Car( const Car &other )
        : idx(other.idx),
          p(other.p),
          prevCar(other.prevCar),
          nextCar(other.nextCar)
{
}

std::string Car::toString() const
{
    return to_string(p);
}

