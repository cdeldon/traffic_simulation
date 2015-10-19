//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_ROAD_H
#define TRAFFIC_SIMULATION_ROAD_H

#include <car.h>
#include <vector>
#include <string>

class Road
{
    public:
        Road();

        Road( const std::vector<Car::position> & );

        void write( std::string filename );

    private:
        std::vector<Car *> lane;

};


#endif //TRAFFIC_SIMULATION_ROAD_H
