#include "Visualizer.h"

uint16_t Visualizer::no_saved = 0;
Hair Visualizer::hair;

//Visualizer::Visualizer()
//{
//}
//
//Visualizer::~Visualizer()
//{
//}

void Visualizer::save_as_ppm()
{
    std::vector<uint8_t> pixels;
    pixels.reserve(IMAGE_HEIGHT * IMAGE_WIDTH * 3);

    glReadBuffer(GL_COLOR_ATTACHMENT3);
    glReadPixels(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    std::reverse(pixels.begin(), pixels.end());

    char buffer [50];
    sprintf (buffer, "pictures/%04d.ppm", no_saved);
    ++no_saved;
    std::ofstream fout(buffer);

    fout << "P3" << std::endl << IMAGE_WIDTH << " " << IMAGE_HEIGHT << std::endl << 255 << std::endl;

    int32_t k = 0;
    for(int32_t i=0; i<IMAGE_WIDTH; i++)
    {
        for(int32_t j=0; j<IMAGE_HEIGHT; j++)
        {
            fout << static_cast<unsigned>(pixels[k]) << " " << static_cast<unsigned>(pixels[k+1]) << " " << static_cast<unsigned>(pixels[k+2]) << std::endl;
            k += 3;
        }
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
    glDrawBuffer(GL_COLOR_ATTACHMENT3);
    Visualizer::save_as_ppm();
}

void Visualizer::update (Hair h) {
    hair = h;
    draw_hair();
}

void Visualizer::init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);
    glutCreateWindow("Hair");
    glutDisplayFunc(Visualizer::draw_hair);
    glutMainLoopEvent();
}
