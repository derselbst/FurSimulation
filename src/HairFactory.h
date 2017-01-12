#pragma once

#include "Vertex.h"

#include <boost/align/aligned_allocator.hpp>
#include <vector>

constexpr size_t Alignment = 64;

template<typename T>
using aligned_vector = std::vector<T, boost::alignment::aligned_allocator<T, Alignment> >;

typedef aligned_vector<Vertex> Strand;
typedef aligned_vector<Strand> Hair;


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
