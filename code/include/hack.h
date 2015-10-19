//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_HACK_H
#define TRAFFIC_SIMULATION_HACK_H

/**
 * Dirty hack to make the function to_string
 * work under MinGW
 */

#ifdef __MINGW32__

#include <sstream>

template< typename T >
std::string to_string( const T &n )
{
    std::ostringstream ost;
    ost << n;
    return ost.str();
}

#endif // __MINGW32__

#endif //TRAFFIC_SIMULATION_HACK_H
