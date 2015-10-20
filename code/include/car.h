//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_CAR_H
#define TRAFFIC_SIMULATION_CAR_H

#include <string>

class Car
{
    public:
        /**
         * definition of the types that
         * play a role for the Car class
         */
        typedef float position;
        typedef float velocity;
        typedef float acceleration;
        typedef float length;

        /**
         * static constant variables that are
         * the same for all objects of the
         * type Car.
         */
        static const velocity V_DESIRED;
        static const position DIST_DESIRED;
        static const acceleration A_MAX;
        static const acceleration D_MAX;
        static const length LENGTH;

        Car( const position, const unsigned int );

        Car( const Car & );

        position getPosition() const
        {
            return p;
        }

        std::string toString() const;

    private:
        const unsigned int idx;

        position p;
        velocity v;

        Car *nextCar = nullptr;
        Car *prevCar = nullptr;
};

#endif //TRAFFIC_SIMULATION_CAR_H
