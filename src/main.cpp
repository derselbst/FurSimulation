
#include "HairFactory.h"
#include "Visualizer.h"

#include "FTL.h"

#include <iostream>

using namespace std;


void print(const Hair& h)
{
    for(size_t s = 0; s<h.size(); s++)
    {
        cout << endl;
        cout << "Strand no. " << s << endl;
        for(size_t v = 0; v<h[s].size(); v++)
        {
            const vec3& pos = h[s][v].Position;

            cout << "X: " << pos.x << " Y: " << pos.y << " Z: " << pos.z << endl;
        }
    }
}


int main(int argc, char** argv)
{
    Hair h = HairFactory::GrowHair(100/*no. strands*/, 50/*no. of vertices per strand*/);
    Visualizer::init(argc, argv);

    FTL ftl(h);
    ftl.addForce(vec3(5,0,0));


    vec3 force;
    vec3 gravity(0,-0.3,0);
    for(int i=0; i<60000; i++)
    {
        if(i%1 == 0)
        {
            Visualizer::update(h);
        }

        ftl.addForce(gravity);
        if(i%10000 == 0)
        {
            force = vec3(10*sin(i), 0, 10*cos(i));
            ftl.addForce(force);
        }
        ftl.update();


    }

//    Visualizer::display(h, argc, argv);

//     print(h);

    return 0;
}
