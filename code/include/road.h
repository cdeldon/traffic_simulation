//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_ROAD_H
#define TRAFFIC_SIMULATION_ROAD_H

#include <common.h>
#include <vector>
#include <queue>
#include <string>

#include <obstacle.h>
#include <car.h>

class Simulation;
extern Simulation * active_simulation;

class Road
{
    public:
        Road(Simulation const * const s = active_simulation);
        Road(const Road &);
        Road(const Road &, Simulation const * const s);
        Road(double speed_limit, double time_headway, double space_headway, Simulation const * const s = active_simulation);
        Road(const std::vector<double> &pos, Simulation const * const s = active_simulation);
        ~Road();

        void populate(const std::vector<Car::position> &);
        void populate(unsigned int n);

        void writePositions(std::string filename) const;

		double getLength() const;

		void addObstacle(const Obstacle &);
		void clearObstacles();

		void addTrafficLight(const TrafficLight &);
		void clearTrafficLights();

		double speedLimit(double x) const;
		double timeHeadway(double x) const;
        double spaceHeadway(double x) const;

        unsigned int find(const Car *) const;

        void setLength(double l) { length = l; }
        void setSpeedLimit(double s) { speed_limit = s; }
        void setTimeHeadway(double t) { time_headway = t; }
        void setSpaceHeadway(double d) { space_headway = d; }

        const Simulation * const getSimulation() const { return simulation; }

        void update(const double dt);

    private:
        void reIndex() const;

		std::vector<Obstacle> obstacles;
        std::vector<TrafficLight> traffic_lights;
        // TODO Keep this as values not as pointers
		std::vector<Car *> cars;

		double length;

        const Simulation * const simulation;

        // General (default) values. Used when no obstacle is present.
		double speed_limit;
		double time_headway;
        double space_headway;

};


#endif //TRAFFIC_SIMULATION_ROAD_H
