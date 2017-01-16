#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "HairFactory.h"
//#include <GL/glut.h>
#include <GL/freeglut.h>

#include <vector>
#include <algorithm>
#include <fstream>

constexpr int16_t IMAGE_WIDTH   = 720;
constexpr int16_t IMAGE_HEIGHT  = 720;

class Visualizer
{
public:
    static uint16_t no_saved;
    static Hair hair;

    Visualizer();
    virtual ~Visualizer();

    static void init(int argc, char **argv);
    static void save_as_ppm();

    static void update(Hair h);

protected:

private:


    static void draw_hair();

};

#endif // VISUALIZER_H
