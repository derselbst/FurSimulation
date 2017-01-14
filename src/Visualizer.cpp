#include "Visualizer.h"

#include <GL/glut.h>

uint16_t Visualizer::no_saved = 0;
Hair Visualizer::hair;

Visualizer::Visualizer()
{
}

Visualizer::~Visualizer()
{
}

void Visualizer::save_as_ppm()
{
    FILE    *output_image;

    std::vector<uint8_t> pixels;
    pixels.reserve(IMAGE_HEIGHT * IMAGE_WIDTH * 3);

    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glReadPixels(00, 00, IMAGE_WIDTH, IMAGE_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    output_image = fopen("image.ppm", "wt");
    fprintf(output_image,"P3\n");
    fprintf(output_image,"%d %d\n",IMAGE_WIDTH,IMAGE_HEIGHT);
    fprintf(output_image,"255\n");

    int32_t k = 0;
    for(int32_t i=0; i<IMAGE_WIDTH; i++)
    {
        for(int32_t j=0; j<IMAGE_HEIGHT; j++)
        {
            fprintf(output_image,"%u %u %u ", pixels[k], pixels[k+1], pixels[k+2]);
            k = k+3;
        }
        fprintf(output_image,"\n");
    }
}

void Visualizer::draw_hair()
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
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    Visualizer::save_as_ppm();
}

void Visualizer::display(Hair h, int argc, char **argv)
{
    hair = h;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);
    glutCreateWindow("Hair");
    glutDisplayFunc(Visualizer::draw_hair);
    glutMainLoop();
}
