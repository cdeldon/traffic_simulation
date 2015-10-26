#ifndef TRAFFIC_SIMULATION_SIMULATION_H
#define TRAFFIC_SIMULATION_SIMULATION_H

#include <road.h>
#include <settings.h>

class Simulation {
public:
    Simulation();
    Simulation(Road & r);

    void readSettings(const char* path);
    void loadDefaultSettings();
    const Settings* getSettings() const { return &settings; }
    Road const * getRoad() const;

    void run();

private:
    void applySettingsChange();
    Settings settings;
    Road road;
    double time;

    double car_length;
};

#endif  // TRAFFIC_SIMULATION_SIMULATION_H