
#include <simulation.h>
#include <settings.h>

Simulation::Simulation()
    : time(0)
{
}

Simulation::Simulation(Road & r)
    : time(0)
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
}

Road const * Simulation::getRoad() const
{
    return &road;
}

