//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_TRANSFORM_H
#define TRAFFIC_SIMULATION_TRANSFORM_H

template <typename T>
inline T to_ms(T kmh)
{
    return (T)((double)kmh)/3.6;
}

template <typename T>
inline T to_kmh(T ms)
{
    return ms*3.6;
}

#endif //TRAFFIC_SIMULATION_TRANSFORM_H
