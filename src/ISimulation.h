#pragma once

#include "Vertex.h"

class ISimulation
{
protected:
    Hair& hair;

    // this is an interface, even if there were no pure virtual methods, allow
    // construction for child classes only
    ISimulation(Hair& h) : hair(h)
    {}

public:

    // no copy or assignment
    ISimulation(ISimulation const&) = delete;
    ISimulation& operator=(ISimulation const&) = delete;

    // virtual destructor for proper cleanup
    virtual ~ISimulation()
    {}


    void addForce(vec3);
    virtual void update() = 0;

};