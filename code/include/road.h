//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_ROAD_H
#define TRAFFIC_SIMULATION_ROAD_H

#include <car.h>
#include <common.h>
#include <vector>
#include <queue>
#include <string>

struct Obstacle
{
	double start;		// position of the start of the obstacle
    double end;			// position of the end of the obstacle

    /**
     * New setpoints
     */
    double speedLimit;	
    double timeHeadway;	//  difference between the time when a vehicle arrives at a point on the highway and the time the next vehicle arrives at the same point

    
    Obstacle(double start, double end, double speedLimit, double timeHeadway)
             : start(start), end(end), speedLimit(speedLimit), timeHeadway(timeHeadway) {}
    Obstacle(double start, double end, double speedLimit)
             : start(start), end(end), speedLimit(speedLimit), timeHeadway(INF) {}
};

class Road
{
    public:
        Road();
        Road(const std::vector<Car::position> &);
        ~Road() { cars.clear(); }

        void populate(const std::vector<Car::position> &);
        void populate(unsigned int n);

        void write(std::string filename);

		double getLength() const;

		void addObstacle(Obstacle &);
		void clearObstacles();

		void addTrafficLight();
		void clearTrafficLights();

		double getSpeedLimit(double x) const;
		double getTimeHeadway(double x) const;

    private:
        void reIndex() const;

		std::vector<Obstacle> obstacles;
		std::vector<Car *> cars;
		double length;
		double speedLimit;
		double timeHeadway;
};


#endif //TRAFFIC_SIMULATION_ROAD_H
