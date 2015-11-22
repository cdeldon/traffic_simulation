
#include <simulation.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

Simulation::Simulation()
    : time(0), road(this), fname(outDir + "cars" + ".dat")
{
}

Simulation::Simulation(Road & r)
    : time(0), road(r, this), fname(outDir + "cars" + ".dat")
{
}

void Simulation::readSettings(const char* path)
{
    settings.readSettings(path);
    applySettingsChange();
}

void Simulation::loadDefaultSettings()
{
    settings = Settings::predefined;
    applySettingsChange();
}

void Simulation::applySettingsChange()
{
    this->fname = outDir + "cars_" + settings.ID + ".dat";

    road.setSpeedLimit(settings.v_desired);
    road.setSpaceHeadway(settings.d_desired);
    road.setTimeHeadway(settings.t_desired);
    road.setLength(settings.road_length);
    road.populate(settings.n_cars, settings.filling);

    road.clearObstacles();
    for (unsigned int i = 0; i < settings.obstacles.size(); ++i)
        road.addObstacle(settings.obstacles[i]);
    for (unsigned int i = 0; i < settings.traffic_lights.size(); ++i)
        road.addTrafficLight(settings.traffic_lights[i]);
}

Road const * Simulation::getRoad() const
{
    return &road;
}

void Simulation::run()
{
    // open output file
    std::ofstream out(fname.c_str());

    unsigned int step = 0;
    unsigned int printStep = 0;
    std::cout<<"\n\n\t\tPROGRESS:\n";
    for(double t = 0; t < settings.end_T; t+=settings.DT)
    {
        // if we must print the simulation
        ++step;
        if(settings.output_freq == 1 || step % settings.output_freq == 1)
        {
            ++printStep;
            out << t << "\t\t";
            if (settings.output_positions) {
                std::vector<double> p = road.getPositions();
                for (unsigned int i = 0; i < p.size(); ++i)
                    out << p[i] << "\t";
            }
            if (settings.output_velocities) {
                out << "\t";
                std::vector<double> v = road.getVelocities();
                for (unsigned int i = 0; i < v.size(); ++i)
                    out << v[i] << "\t";
            }
            if (settings.output_positions) {
               out << "\t" << road.getTroughput();
            }
            out << std::endl;
        }

        drawProgress(((float) step)/(settings.end_T*1./settings.DT),
                     ((float) (step-1)/(settings.end_T*1./settings.DT)));

        // delegate the update of the car position to the road
        road.update(settings.DT);

        // check for crashes
        double crash = -1;
        std::vector<double> cars = road.getPositions();
        for (unsigned int i = 1; i < cars.size(); ++i)
            if (std::fmod(cars[i] - cars[i - 1] + settings.road_length, settings.road_length) < settings.car_size)
                crash = cars[i];
        if (std::fmod(cars[0] - cars[cars.size() - 1] + settings.road_length, settings.road_length) < settings.car_size)
            crash = cars[0];
        if (crash != -1) {
            std::cout << std::endl << "Crash at position " << crash << " and time t=" << time << ". Aborting." << std::endl;
#if 1
            out << t << "\t\t";
            if (settings.output_positions) {
                std::vector<double> p = road.getPositions();
                for (unsigned int i = 0; i < p.size(); ++i)
                    out << p[i] << "\t";
            }
            if (settings.output_velocities) {
                out << "\t";
                std::vector<double> v = road.getVelocities();
                for (unsigned int i = 0; i < v.size(); ++i)
                    out << v[i] << "\t";
            }
            if (settings.output_positions) {
                out << "\t" << road.getTroughput();
            }
            out << std::endl;
#endif
            return;
        }
        time += settings.DT;
    }

    std::cout<<"\n\n";
    std::cout<<"==========================================================\n";

    out.close();
}

void Simulation::drawProgress(double percent, double oldpercent, unsigned int l)
{
    // old bar and new bar
    std::string Old;
    std::string New;

    for (unsigned int i = 0; i<l; ++i) {
        if(i < (unsigned int)(l * percent))
            New += "#";
        else {
            New += " ";
        }
        if (i < (unsigned int)(l * oldpercent))
            Old += "#";
        else {
            Old += " ";
        }
    }

    // check if the bar has to be redrawn
    if(Old != New) {
        std::cout << "\r";
        std::cout << std::setprecision(3) << "[ " << New << " ] " << percent * 100 << "%" << std::flush;
    }
        return;

}

