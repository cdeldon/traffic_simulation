
#include <simulation.h>
#include <settings.h>

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
    // TODO: call Road::update() looping over time
    // write out the data depending on OUT_FREQ
}

