
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

void usage(char* progname)
{
    cout << "Usage: " << progname << " [OPTION]...\n\n"
         << "\t available options are: \n"
         << "\t\t --nogl\t\tdont use openGL and dont render anything\n"
         << "\t\t --write\tcreate SGI images for every rendered frame (--nogl has priority)\n"
         << "\t\t --ftl\t\tuse simulation method 'Follow the Leader' (default)\n"
         << "\t\t --pbd\t\tuse simulation method 'Position Based Dynamics'\n" << endl;
    
}


int main(int argc, char** argv)
{
constexpr int Frames = 10000;


bool useFTL=true, useGL=true, writeImg=false;
for(int i=1; i<argc; i++)
{
    string arg = string(argv[i]);
    if(arg == "--help" || arg == "-h")
    {
        usage(argv[0]);
        return 0;
    }
    else if (arg == "--write")
    {
        writeImg = true;
        useGL = true;
    }
    else if(arg == "--nogl")
    {
        useGL = false;
        writeImg = false;
    }
    else if(arg == "--pbd")
    {
        useFTL = false;
    }
    else if(arg == "--ftl")
    {
        useFTL = true;
    }
    else
    {
        cerr << "Ignoring unknown flag: " << arg << endl;
    }
}


    Hair h = HairFactory::GrowHair(1000/*no. strands*/, 50/*no. of vertices per strand*/);

    if(useGL)
    {
    Visualizer::init(argc, argv);
    }

    ISimulation* sim;
    if(useFTL)
    {
        sim = new FTL(h);
    }
    else
    {
        sim = new PBD(h);
    }

    // add an initial force
    sim->addForce(vec3(5,0,0));

    
    vec3 gravity(0,-0.3,0);
std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
std::chrono::nanoseconds dur(0);
    for(int i=0; i<Frames; i++)
    {
        if(useGL)
        {
            Visualizer::update(h, writeImg);
        }

        sim->addForce(gravity);
        if(i%5000 == 0)
        {
            vec3 force = vec3(10*sin(i), 0, 10*cos(i));
            sim->addForce(force);
        }
        
start = std::chrono::high_resolution_clock::now();
        sim->update();
end = std::chrono::high_resolution_clock::now();
dur +=  std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
    }

 
    std::cout << "elapsed time for one update() call: " << dur.count()/(Frames * 1000.0) << "us\n";

    return 0;
}
