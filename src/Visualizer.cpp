#include "Visualizer.h"

#include <exception>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <string.h>

using namespace std;
using chrono::system_clock;
using chrono::duration;

uint16_t Visualizer::no_saved = 0;
Hair Visualizer::hair;


/**save_as_wbmp is obsolete, use save_as_sgi instead**/
/*
    save 720x720 picture in wbmp-format (not ASCII-coded)
*/
void Visualizer::save_as_wbmp()
{
    std::vector<uint8_t> pixels;
    pixels.reserve(IMAGE_HEIGHT * IMAGE_WIDTH);

    glReadBuffer(GL_COLOR_ATTACHMENT1);
    glReadPixels(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, GL_RED, GL_UNSIGNED_BYTE, pixels.data());
    vector<bool> bPix(pixels.begin(), pixels.begin()+720*720);

    static char buffer [50];
    sprintf (buffer, "pictures/%04d.wbmp", no_saved);
    ++no_saved;
    std::ofstream fout(buffer, ios::binary);

    if(!fout.good())
    {
        throw std::runtime_error("something is wrong with outstream for ppm. does the pictures directory exist?");
    }


    vector<bool> header = { 0,0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0,
                            1,0,1,0,0,0,0,1,
                            0,0,0,0,1,0,1,0,
                            1,0,1,0,0,0,0,1,
                            0,0,0,0,1,0,1,0
                          };

    //some wild memory copy
    char* headerBuf = new char[6];
    auto t = header.begin()._M_p;
    memcpy(&headerBuf[0], t, 6);

    fout.write(headerBuf, 6);
    delete headerBuf;

    char* dataBuf = new char[64800];
    auto dataTmp = bPix.begin()._M_p;

    memcpy(&dataBuf[0], dataTmp, 64800);
    fout.write(dataBuf, 64800);

    delete dataBuf;
}

void Visualizer::save_as_sgi()
{
// better use htobe16 here, however, depending on implementatiion, only allowed in blockscope
    typedef struct
    {
        int16_t imagic = __builtin_bswap16(474);
        int8_t type = 0;// uncompressed
        int8_t bpc = 1;// 1 byte per channel
        uint16_t dim = __builtin_bswap16(2); // usual 2D img
        uint16_t xsize = __builtin_bswap16(IMAGE_WIDTH);
        uint16_t ysize = __builtin_bswap16(IMAGE_HEIGHT);
        uint16_t zsize = __builtin_bswap16(1); // 1 channel, i.e. grayscale
        int32_t min = __builtin_bswap32(0);
        int32_t max = __builtin_bswap32(255);
        char dummy[4] = {};
        char name[80] = {};
        int32_t colorMap = __builtin_bswap32(0);
        char dummyy[404] = {};
    } SGI_RGB_HEADER;

    static const SGI_RGB_HEADER header {};

    std::vector<uint8_t> pixels;
    pixels.reserve(IMAGE_HEIGHT * IMAGE_WIDTH);

    glReadBuffer(GL_COLOR_ATTACHMENT1);
    glReadPixels(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, GL_RED, GL_UNSIGNED_BYTE, pixels.data());


    static char buffer [50];
    sprintf (buffer, "pictures/%04d.sgi", no_saved);
    ++no_saved;
    std::ofstream fout(buffer);
    if(!fout.good())
    {
        throw std::runtime_error("something is wrong with outstream for ppm. does the pictures directory exist?");
    }


    fout.write(reinterpret_cast<const char*>(&header), sizeof(header));
    fout.write(reinterpret_cast<const char*>(pixels.data()), IMAGE_HEIGHT * IMAGE_WIDTH * sizeof(uint8_t));
}

/**save_as_ppm is obsolete, use save_as_sgi instead**/
void Visualizer::save_as_ppm()
{
    std::vector<uint8_t> pixels;
    pixels.reserve(IMAGE_HEIGHT * IMAGE_WIDTH * 3);

    glReadBuffer(GL_COLOR_ATTACHMENT1);
    glReadPixels(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

//    std::reverse(pixels.begin(), pixels.end());//not necessary

    static char buffer [50];
    sprintf (buffer, "pictures/%04d.ppm", no_saved);
    ++no_saved;
    std::ofstream fout(buffer);
    if(!fout.good())
    {
        throw std::runtime_error("something is wrong with outstream for ppm. does the pictures directory exist?");
    }

    fout << "P3" << "\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n" << 255 << "\n";

//    too slow better use binary write
    int32_t k = 0;
    for(int32_t i=0; i<IMAGE_HEIGHT; i++)
    {
        for(int32_t j=0; j<IMAGE_WIDTH; j++)
        {
            fout << static_cast<unsigned>(pixels[k]) << " " << static_cast<unsigned>(pixels[k+1]) << " " << static_cast<unsigned>(pixels[k+2]) << " ";
            k += 3;
        }
        fout<<"\n";
    }
}

void Visualizer::draw_hair(bool writeImg)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    for(size_t s = 0; s<hair.size(); s++)
    {
        for(size_t v = 0; v<hair[s].size()-1; v++)
        {
            glVertex3f(hair[s][v].Position.x, hair[s][v].Position.y, hair[s][v].Position.z);
            glVertex3f(hair[s][v+1].Position.x, hair[s][v+1].Position.y, hair[s][v+1].Position.z);
        }
    }
    glEnd();
    glFlush();
    glDrawBuffer(GL_COLOR_ATTACHMENT1);

    if(writeImg)
    {
        Visualizer::save_as_sgi();
    }
}

void Visualizer::update (Hair h, bool writeImg)
{
    hair = h;
    draw_hair(writeImg);
}

void Visualizer::init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);
    glutCreateWindow("Hair");
    glutMainLoopEvent();
}
