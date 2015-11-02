
#include <simulation.h>
#include <iostream>
#include <iomanip>

Simulation::Simulation()
    : time(0), road(this)
{
}

Simulation::Simulation(Road & r)
    : time(0), road(r, this)
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
    road.setLength(settings.road_length);
    road.populate(settings.n_cars);

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
    unsigned int step = 0;
    unsigned int printStep = 0;
    std::cout<<"\n\n\t\tPROGRESS:\n";
    for(double t = 0; t < settings.end_T; t+=settings.DT)
    {
        // if we must print the simulation
        ++step;
        if(step % settings.output_freq == 1)
        {
            ++printStep;
            // TODO set the string for the ouput path
            road.writePositions("../../output/cars" + to_string(printStep) + ".dat");
        }

        drawProgress(((float) step)/(settings.end_T*1./settings.DT),
                     ((float) (step-1)/(settings.end_T*1./settings.DT)));

        // delegate the update of the car position to the road
        road.update(settings.DT);
    }

    std::cout<<"\n\n";
    std::cout<<"==========================================================\n";
}

void Simulation::drawProgress(double percent, double oldpercent, unsigned int l)
{
    // old bar and new bar
    std::string Old;
    std::string New;

    for (int i=0; i<l; ++i) {
        if(i < int(l * percent))
            New += "#";
        else {
            New += " ";
        }
        if(i < int(l * oldpercent))
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

