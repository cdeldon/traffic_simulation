//
// Created by Carlo on 18.10.2015.
//

#include <road.h>
#include <fstream>
#include <iomanip>
#include <algorithm>

#define DEFAULT_SPEEDLIMIT 30.0
#define DEFAULT_TIMEHEADWAY 1.5

Road::Road()
	: speedLimit(DEFAULT_SPEEDLIMIT), timeHeadway(DEFAULT_TIMEHEADWAY)
{
}

void Road::reIndex() const
{
    for (unsigned int i = 1; i < cars.size(); ++i) {
        cars[i]->prevCar = cars[i - 1];
        cars[i - 1]->nextCar = cars[i];
    }
    cars[0]->nextCar = NULL;
    cars[cars.size() - 1]->prevCar = NULL;
}


void Road::populate(const std::vector<Car::position> & pos)
{
	cars.clear();
	cars.resize(pos.size());
	for (unsigned int i = 0; i < pos.size(); ++i)
		cars[i] = new Car(pos[i]);

    reIndex();        
}

void Road::populate(unsigned int n)
{
    cars.clear();
    cars.resize(n);
    for (unsigned int i = 0; i < n; ++i) {
        cars[i] = new Car(length/n * i);
    }
    reIndex();
}


Road::Road(const std::vector<double> &pos)
	: speedLimit(DEFAULT_SPEEDLIMIT), timeHeadway(DEFAULT_TIMEHEADWAY)
{
	populate(pos);
}


void Road::write(std::string filename)
{
    std::ofstream out(filename.c_str());
    out << std::setprecision(5);
	for (unsigned int i = 0; i < cars.size(); ++i)
    {
		out << cars[i]->toString() << " \t ";
    }
    out.close();
}


double Road::getLength() const
{
	return length;
}

void Road::addObstacle(Obstacle & o)
{
	obstacles.push_back(o);
}

void Road::clearObstacles()
{
	obstacles.clear();
}

/**
* Returns the desired speed limit at position x. It is given by the most stringent (i.e. lowest) limit of any obstacle at that position.
*/
double Road::getSpeedLimit(double x) const
{
    double result = speedLimit;

    for (unsigned i = 0; i < obstacles.size(); ++i) {
        if (obstacles[i].start < x && x < obstacles[i].end)
            result = std::min(result, obstacles[i].speedLimit);
    }

    return result;
}

/**
* Returns the desired time headway at position x. It is given by the most stringent (i.e. highest) limit of any obstacle at that position.
*/
double Road::getTimeHeadway(double x) const
{
    double result = timeHeadway;

    for (unsigned i = 0; i < obstacles.size(); ++i) {
        if (obstacles[i].start < x && x < obstacles[i].end)
            result = std::max(result, obstacles[i].timeHeadway);
    }

    return result;
}