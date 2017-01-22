
#define restrict __restrict__
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
    constexpr float TimeStep = 1.0f/200.0f; // mentioned as dt
    constexpr float Damping = 0.95f; //sDamping

    for(size_t s=0; s < this->hair.size(); s++)
    {
        for(size_t v=1 /*skip the very first vertex*/; v < this->hair[s].size(); v++)
        {
            Vertex& x = this->hair[s][v];

            x.OldPosition = x.Position;
            // accululate forces here
        }
    }

    for(size_t s=0; s < this->hair.size(); s++)
    {
        for(size_t v=1 /*skip the very first vertex*/; v < this->hair[s].size(); v++)
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
        for(size_t v=1 /*skip the very first vertex*/; v < this->hair[s].size(); v++)
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

            // correction vector for satisfying the constraint
            x.Correction = x.Position - x.Correction;
            // end solve constraint
        }
    }

    Strand* restrict str = this->hair.data();
    for(size_t s=0; s < this->hair.size(); s++)
    {
        Vertex* restrict x = str[s].data();
        const size_t nVert = this->hair[s].size();
        for(size_t v=1; v < nVert; v++)
        {            
            x[v].Velocity = ((x[v].Position - x[v].OldPosition) / TimeStep);

            // correct the velocity with the correction vector computed for previous vertex
            // obviously this is not possible for the last particle, so add 0 in this case
            x[v].Velocity += (v+1>=this->hair[v].size()) ? vec3(0,0,0) : Damping * (-x[v+1].Correction / TimeStep); // (9)
            
//             x[v].OldPosition = x[v].Position;
        }
    }
}
