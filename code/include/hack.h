//
// Created by Carlo on 18.10.2015.
//

#ifndef TRAFFIC_SIMULATION_HACK_H
#define TRAFFIC_SIMULATION_HACK_H

/**
 * The function std::to_string seems to be unavailable in some versions of MinGW.
 * We thus define our own.
 */

//#if defined( __MINGW32__) || defined(_MSC_VER)

#include <sstream>

template< typename T >
std::string to_string( const T &n )
{
    std::ostringstream ost;
    ost << n;
    return ost.str();
}

template <typename T>
T clip(const T& a, const T& lower, const T& upper)
{
    return std::max(lower, std::min(upper,a));
}

//#endif // defined( __MINGW32__) || defined(_MSC_VER)

#endif //TRAFFIC_SIMULATION_HACK_H
