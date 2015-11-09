//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_COMMON_H
#define TRAFFIC_SIMULATION_COMMON_H

#include <hack.h>

#define INF (2<<30)

class Simulation;

extern Simulation * active_simulation;

#if defined(_MSC_VER)
    static std::string outDir = "../output/";
#else
    static std::string outDir = "../../output/";
#endif



#endif //TRAFFIC_SIMULATION_COMMON_H
