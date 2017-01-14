#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "HairFactory.h"

#include <vector>
#include <algorithm>

constexpr int16_t IMAGE_WIDTH   = 720;
constexpr int16_t IMAGE_HEIGHT  = 720;

class Visualizer
{
public:
    static uint16_t no_saved;
    static Hair hair;

    Visualizer();
    virtual ~Visualizer();

    static void display(Hair h, int argc, char **argv);
    static void save_as_ppm();

protected:

private:


    static void draw_hair();

};

#endif // VISUALIZER_H
