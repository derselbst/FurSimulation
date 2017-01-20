
#define restrict __restrict__
#include "FTL.h"

FTL::FTL(Hair& h) : ISimulation(h)
{}

FTL::~FTL()
{}

void FTL::addForce(vec3 f)
{
Strand* restrict str = this->hair.data();
//#pragma omp simd aligned(str:Alignment)
//#pragma vector aligned
    for(size_t s=0; s < this->hair.size(); s++)
    {
	Vertex* restrict vert = str[s].data();
#pragma omp simd aligned(vert:Alignment)
#pragma vector aligned
      for(size_t v=0; v < str[s].size(); v++)
      {
         vert[v].Force += f;
      }
    }
}

void FTL::update()
{
  constexpr float TimeStep = 1.0f/125.0f; // mentioned as dt
  constexpr float Damping = 0.9f; //sDamping

Strand* restrict str = this->hair.data();
#pragma omp parallel for schedule(static)
    for(size_t s=0; s < this->hair.size(); s++)
    {
      Vertex* restrict x = str[s].data();
      const size_t nVert = this->hair[s].size();
      #pragma omp simd aligned(x:Alignment)
      #pragma vector aligned
      for(size_t v=nVert-1; v >= 1; v--)
      {
	// calc new position
	vec3 p = x[v].Position + TimeStep * x[v].Velocity + TimeStep*TimeStep * x[v].Force; // (1)
	
	
	// solve constraints - (2)
            Vertex& pre = str[s][v-1];
            
            vec3 direction = p - pre.Position;
            direction = glm::normalize(direction);
            
            // backup x's new position before we're going to constraint it
            vec3 pBackup = p;
            
            // constraint the new position of vertex x on a sphere of radius l0 around previous vertex
            p = pre.Position + direction * pre.L0;
	// end solve constraint
            
	// update velocity + final position + force
// 	x.Velocity = (p - x.Position) / TimeStep; // (3)
	x[v].Velocity = ((p - x[v].Position) / TimeStep);
        
        // correct the velocity with the correction vector computed for previous vertex
        // obviously this is not possible for the last particle, so add 0 in this case
        x[v].Velocity += (v+1>=nVert) ? vec3(0,0,0) : Damping * (-x[v+1].Correction / TimeStep); // (9)
	
	x[v].Position = p; // (4)
	
        // correction vector for satisfying the constraint
        // needed when correcting velocity in next iteration
	x[v].Correction = p - pBackup; // (6)
	
	x[v].Force = vec3(0,0,0);
      }
    }
}
