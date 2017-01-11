
#include "FTL.h"

FTL::FTL(Hair& h) : ISimulation(h)
{}

void FTL::addForce(vec3 f)
{
    for(size_t s=0; s < this->hair.size(); s++)
    {
      for(size_t v=0; v < this->hair[v].size(); v++)
      {
         this->hair[s][v]->Force += f;
      }
    }
}

void FTL::update()
{
  const float TimeStep = 1.0f/10.0f; // mentioned as dt
  
    for(size_t s=0; s < this->hair.size(); s++)
    {
      for(size_t v=1 /*skip the very first vertex*/; v < this->hair[v].size(); v++)
      {
	Vertex& x = this->hair[s][v];
	
	// calc new position
	vec3 p = x.Position + TimeStep * x.Velocity + TimeStep*TimeStep * x.Force;
	
	// TODO solve constraints
	
	x.Velocity = (p - x.Position) / TimeStep;
	x.Position = p;
	x.Force = 0;
      }
    }
    
}