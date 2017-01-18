
#include "PBD.h"

PBD::PBD(Hair& h) : ISimulation(h)
{}

PBD::~PBD()
{}

void PBD::addForce(vec3 f)
{
    for(size_t s=0; s < this->hair.size(); s++)
    {
      for(size_t v=0; v < this->hair[v].size(); v++)
      {
         this->hair[s][v].Force += f;
      }
    }
}

void PBD::update()
{
  constexpr float TimeStep = 1.0f/20.0f; // mentioned as dt
  
    for(size_t s=0; s < this->hair.size(); s++)
    {
      for(size_t v=1 /*skip the very first vertex*/; v < this->hair[v].size(); v++)
        {
            Vertex& x = this->hair[s][v];
            
            x.OldPosition = x.Position;
            // accululate forces here
        }
    }
    
    for(size_t s=0; s < this->hair.size(); s++)
    {
      for(size_t v=1 /*skip the very first vertex*/; v < this->hair[v].size(); v++)
        {
            Vertex& x = this->hair[s][v];
     
            vec3 acceleration = x.Force / x.Mass;
            x.Velocity += TimeStep * acceleration;
            x.Position += TimeStep * x.Velocity;
        }
    }

    for(size_t s=0; s < this->hair.size(); s++)
    {
      for(size_t v=1 /*skip the very first vertex*/; v < this->hair[v].size(); v++)
        {
            Vertex& x = this->hair[s][v];
            // solve constraints
                Vertex& pre = this->hair[s][v-1];
                
                vec3 direction = x.Position - pre.Position;
                direction = glm::normalize(direction);
                
                // constraint the new position of vertex x on a sphere of radius l0 around previous vertex
                x.Position = pre.Position + direction * pre.L0;
            // end solve constraint
        }
    }
    
    for(size_t s=0; s < this->hair.size(); s++)
    {
      for(size_t v=1 /*skip the very first vertex*/; v < this->hair[v].size(); v++)
        {
            Vertex& x = this->hair[s][v];
            x.Velocity += (x.Position - x.OldPosition) / TimeStep;
        }
    }
}
