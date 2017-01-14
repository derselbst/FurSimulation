
#include "FTL.h"

FTL::FTL(Hair& h) : ISimulation(h)
{}

FTL::~FTL()
{}

void FTL::addForce(vec3 f)
{
    for(size_t s=0; s < this->hair.size(); s++)
    {
      for(size_t v=0; v < this->hair[v].size(); v++)
      {
         this->hair[s][v].Force += f;
      }
    }
}

void FTL::update()
{
  constexpr float TimeStep = 1.0f/20.0f; // mentioned as dt
  constexpr float Damping = 0.9f; //sDamping
  
    for(size_t s=0; s < this->hair.size(); s++)
    {
      for(size_t v=1 /*skip the very first vertex*/; v < this->hair[v].size(); v++)
      {
	Vertex& x = this->hair[s][v];
	
	// calc new position
	vec3 p = x.Position + TimeStep * x.Velocity + TimeStep*TimeStep * x.Force; // (1)
	
	
	// solve constraints - (2)
            Vertex& pre = this->hair[s][v-1];
            
            vec3 direction = p - pre.Position;
            direction = glm::normalize(direction);
            
            // backup x's new position before we're going to constraint it
            vec3 pBackup = p;
            
            // constraint the new position of vertex x on a sphere of radius l0 around previous vertex
            p = pre.Position + direction * pre.L0;
	// end solve constraint
        
        
        // correction vector for satisfying the constraint
        vec3 d = pBackup - p; // (6)
	
	// update velocity + final position + force
// 	x.Velocity = (p - x.Position) / TimeStep; // (3)
	x.Velocity = ((p - x.Position) / TimeStep) + Damping * (-d / TimeStep); // (9)
	
	x.Position = p; // (4)
	
	x.Force = vec3(0,0,0);
      }
    }
}