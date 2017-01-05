#pragma once

class HairFactory
{
    // no object
    HairFactory() = delete;
    // no copy
    HairFactory(const HairFactory&) = delete;
    // no assign
    HairFactory& operator=(const HairFactory&) = delete;

typedef vector<Vertex> Strand;
typedef vector<Strand> Hair;

static Hair GrowHair();

// @idea another growhair method may receive a kind of 2d black/white texture that specifies where to grow strands
};
