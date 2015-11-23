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


        Car(const position, Road* const);
        Car(const position, const velocity, Road* const);
        Car(const Car & );
        Car(const Car &, Road * const);

        position getPosition() const { return p; }
        void setPosition(double p_){this->p = p_;}
        velocity getVelocity() const { return v; }
        void setVelocity(velocity v_){this->v = v_;}
        acceleration getAcceleration(const double dt, bool & stop_light) const;

        std::string toString() const;

        unsigned int index() const;

        void update_postion(const double dt);

        static bool comp(Car * c1, Car * c2) { return c1->getPosition() < c2->getPosition(); }

    private:

        position p;
        velocity v;
        Car * next_car;
        Car * prev_car;
        Road * const road;
};

#endif //TRAFFIC_SIMULATION_CAR_H
