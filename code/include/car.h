//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_CAR_H
#define TRAFFIC_SIMULATION_CAR_H

#include <string>

class Road;

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


        Car(const position, const Road* const);
        Car(const position, const velocity, const Road* const);
        Car(const Car & );
        Car(const Car &, const Road * const);

        position getPosition() const { return p; }
        velocity getVelocity() const { return v; }
        acceleration getAcceleration() const;

        std::string toString() const;

        unsigned int index() const;

    private:

        position p;
        velocity v;
        Car * next_car;
        Car * prev_car;
        const Road * const road;
};

#endif //TRAFFIC_SIMULATION_CAR_H
