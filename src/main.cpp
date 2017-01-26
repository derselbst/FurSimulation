
#include "HairFactory.h"
#include "Visualizer.h"

#include "FTL.h"
#include "PBD.h"

#include <iostream>
#include <chrono>

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
constexpr int Frames = 100000;

std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    Hair h = HairFactory::GrowHair(100/*no. strands*/, 10/*no. of vertices per strand*/);
    Visualizer::init(argc, argv);

    PBD ftl(h);
    ftl.addForce(vec3(5,0,0));


    vec3 force;
    vec3 gravity(0,-0.3,0);
start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<Frames; i++)
    {
        if(i%1 == 0)
        {
            Visualizer::update(h);
        }

        ftl.addForce(gravity);
        if(i%5000 == 0)
        {
            force = vec3(10*sin(i), 0, 10*cos(i));
            ftl.addForce(force);
        }
        ftl.update();
    }

end = std::chrono::high_resolution_clock::now();
auto dur =  std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
 
    std::cout << "elapsed time: " << dur.count()/static_cast<double>(Frames) << "ms\n";

    return 0;
}
