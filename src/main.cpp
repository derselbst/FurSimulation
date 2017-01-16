
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
    Hair h = HairFactory::GrowHair(100/*no. strands*/, 10/*no. of vertices per strand*/);
    Visualizer::init(argc, argv);    

    FTL ftl(h);
    vec3 force(10,0,0);
    ftl.addForce(force);
    
    for(int i=0; i<60000; i++)
    {
        ftl.update();
        Visualizer::update(h);
    }
    
//    Visualizer::display(h, argc, argv);
        
//     print(h);
    
    return 0;
}
