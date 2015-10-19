//
// Created by Carlo on 18.10.2015.
//
#include <road.h>
#include <fstream>
#include <iomanip>

Road::Road()
{
}

Road::Road( const std::vector<float> &pos )
{
    lane.resize(pos.size());
    for ( int i = 0; i < pos.size(); ++i )
    {
        lane[i] = new Car(pos[i], i);
    }
}

void Road::write( std::string filename )
{
    std::ofstream out(filename.c_str());
    out << std::setprecision(5);
    for ( int i = 0; i < lane.size(); ++i )
    {
        out << lane[i] -> toString() << " \t ";
    }
    out.close();
}