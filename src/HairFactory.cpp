#include "HairFactory.h"

using namespace std;

Hair HairFactory::GrowHair(const size_t nStrands, const size_t nVert)
{
    Hair hair;//(nStrands, vector<Vertex>(nVert, Vertex() ))
    vec3 startPos(-0.87,0.5,0);
    const double Len = 0.5;
    Vertex::L0 = Len/nVert;

    for(size_t s=0; s<nStrands; s++)
    {
        hair.push_back(aligned_vector<Vertex>());
        Strand& strand = hair.back();

        Vertex particle(startPos, 1.0f);
        for(size_t v=0; v<nVert; v++)
        {
            strand.push_back(particle);

            // place next particle above the current one
            particle.Position.y += Vertex::L0;
        }

        // go to the right
        startPos.x += 0.007; // some rand val here
    }

    return hair;
}

Hair HairFactory::GrowHairOnPlane(const size_t nStrands, const size_t nVert)
{
    Hair hair;//(nStrands, vector<Vertex>(nVert, Vertex() ))
    vec3 startPos(0,0.5,0);
    const size_t Layers = 2;
    const double Len = 0.5;
    
    Vertex::L0 = Len/nVert;

    
    for(size_t layer=0; layer < Layers; layer++)
    {
        startPos.x = -0.8 +  (layer*0.015 / Layers);
        startPos.z = layer*0.5;
        for(size_t s=0; s<nStrands; s++)
        {
            hair.push_back(aligned_vector<Vertex>());
            Strand& strand = hair.back();

            Vertex particle(startPos, 1.0f);
            for(size_t v=0; v<nVert; v++)
            {
                strand.push_back(particle);

                // place next particle above the current one
                particle.Position.y += Vertex::L0;
            }

            // go to the right
            startPos.x += 0.015; // some rand val here
        }
    }

    return hair;
}
