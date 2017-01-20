
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
  constexpr float Damping = 0.96f; //sDamping
  
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
     
            const vec3 acceleration = x.Force / x.Mass;
            x.Velocity += TimeStep * acceleration;
            x.Position += TimeStep * x.Velocity;
            x.Force = vec3(0,0,0);
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
                
                // backup x's unconstrained position
                x.Correction = x.Position;

                // constraint the new position of vertex x on a sphere of radius l0 around previous vertex
                x.Position = pre.Position + direction * pre.L0;

                x.Correction = x.Position - x.Correction;
            // end solve constraint
        }
    }
    
    for(size_t s=0; s < this->hair.size(); s++)
    {
      for(size_t v=1 /*skip the very first vertex*/; v < this->hair[v].size(); v++)
        {
            Vertex& x = this->hair[s][v];
            x.Velocity += (x.Position - x.OldPosition) / TimeStep + Damping * (x.Correction / TimeStep);
        }
    }
}
