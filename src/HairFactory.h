#pragma once

#include "Vertex.h"

class HairFactory
{
public:
    // no object
    HairFactory() = delete;
    // no copy
    HairFactory(const HairFactory&) = delete;
    // no assign
    HairFactory& operator=(const HairFactory&) = delete;


    static Hair GrowHair(const size_t nStrands, const size_t nVert);
    static Hair GrowHairOnPlane(const size_t nStrands, const size_t nVert);

// @idea another growhair method may receive a kind of 2d black/white texture that specifies where to grow strands
};
