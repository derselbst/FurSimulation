#pragma once

#include "Vertex.h"

#include <vector>

typedef std::vector<Vertex> Strand;
typedef std::vector<Strand> Hair;

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

// @idea another growhair method may receive a kind of 2d black/white texture that specifies where to grow strands
};
