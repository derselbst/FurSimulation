#include "HairFactory.h"

using namespace std;

Hair HairFactory::GrowHair(const size_t nStrands, const size_t nVert)
{
	Hair hair;//(nStrands, vector<Vertex>(nVert, Vertex() ))
	vec3 startPos(0,0,0);
	const double Len = 10.0;
	for(size_t s=0; s<nStrands; s++)
	{
		hair.push_back(vector<Vertex>());
		Strand& strand = hair.back();

		Vertex particle(startPos, 1.0f);
		for(size_t v=0; v<nVert; v++)
		{
			strand.push_back(particle);
                        
                        // place next particle above the current one
			particle.y += Len/nVert;
		}
		
		// go to the right
		startPos.x += 0.01; // some rand val here
	}
	
	return hair;
}
