
#include "ISimulation.h"

void ISimulation::addForce(vec3 f)
{
    Strand* restrict str = this->hair.data();

    #pragma omp parallel for schedule(static)
    for(size_t s=0; s < this->hair.size(); s++)
    {
        Vertex* restrict vert = str[s].data();
        size_t nVert = str[s].size();
        #pragma omp simd aligned(vert:Alignment)
        for(size_t v=0; v < nVert; v++)
        {
            vert[v].Force += f;
        }
    }
}
