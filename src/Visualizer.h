#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "HairFactory.h"
//#include <GL/glut.h>
#include <GL/freeglut.h>

#include <vector>
#include <algorithm>
#include <fstream>

constexpr int16_t IMAGE_WIDTH   = 1920;
constexpr int16_t IMAGE_HEIGHT  = 1080;

class Visualizer
{
public:
    static uint16_t no_saved;
    static Hair hair;

    Visualizer();
    virtual ~Visualizer();

    static void init(int argc, char **argv);
    static void save_as_ppm();
    static void save_as_wbmp();
    static void save_as_sgi();

    static void update(Hair h, bool writeImg=false);

private:
    static void draw_hair(bool writeImg);

};

#endif // VISUALIZER_H
