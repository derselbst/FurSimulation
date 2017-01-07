
#include "HairFactory.h"

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


int main()
{
    Hair h = HairFactory::GrowHair(20/*no. strands*/, 10/*no. of vertices per strand*/);
    
    print(h);
    
    return 0;
}