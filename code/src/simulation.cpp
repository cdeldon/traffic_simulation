
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
    // add obstacles to road
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

