//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_CAR_H
#define TRAFFIC_SIMULATION_CAR_H

#include <string>

class Car
{
    friend class Road;

    public:
        /**
         * definition of the types that
         * play a role for the Car class
         */
        typedef double position;
        typedef double velocity;
        typedef double acceleration;
        typedef double length;


        Car( const position);
        Car( const position, const velocity);
        Car( const Car & );

        position getPosition() const { return p; }
        velocity getVelocity() const { return v; }
        acceleration getAcceleration() const;

        std::string toString() const;

    private:

        position p;
        velocity v;
        Car * nextCar;
        Car * prevCar;
};

#endif //TRAFFIC_SIMULATION_CAR_H
