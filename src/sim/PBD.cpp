
#include "PBD.h"

PBD::PBD(Hair& h) : ISimulation(h)
{}

PBD::~PBD()
{}

void PBD::update()
{
    constexpr float TimeStep = 1.0f/100.0f; // mentioned as dt
    constexpr float Damping = 0.95f; //sDamping

    Strand* restrict str = this->hair.data();
    #pragma omp parallel for schedule(static) firstprivate(str) default(none)
    for(size_t s=0; s < this->hair.size(); s++)
    {
        const size_t nVert = str[s].size();
	Vertex* restrict x = str[s].data();

        #pragma omp simd aligned(x:Alignment)
        #pragma vector aligned
        for(size_t v=1 /*skip the very first vertex*/; v < nVert; v++)
        {
            x[v].OldPosition = x[v].Position;
            // actually accululate forces here, but we already did that outside
        }
    }

    #pragma omp parallel for schedule(static) firstprivate(str) default(none)
    for(size_t s=0; s < this->hair.size(); s++)
    {
        const size_t nVert = str[s].size();
	Vertex* restrict x = str[s].data();

        #pragma omp simd aligned(x:Alignment)
        #pragma vector aligned
        for(size_t v=1; v < nVert; v++)
        {
            const vec3 acceleration = x[v].Force / x[v].Mass;
            x[v].Velocity += TimeStep * acceleration;
            x[v].Position += TimeStep * x[v].Velocity;
            x[v].Force = vec3(0,0,0);
        }
    }

    const float L0 = Vertex::L0;
    #pragma omp parallel for schedule(static) firstprivate(str,L0) default(none)
    for(size_t s=0; s < this->hair.size(); s++)
    {
        const size_t nVert = str[s].size();
	Vertex* restrict x = str[s].data();

        #pragma omp simd aligned(x:Alignment)
        #pragma vector aligned
        for(size_t v=1; v < nVert; v++)
        {
            // solve constraints

            vec3 direction = x[v].Position - x[v-1].Position;
            direction = glm::normalize(direction);

            // backup x's unconstrained position
            x[v].Correction = x[v].Position;

            // constraint the new position of vertex x on a sphere of radius l0 around previous vertex
            x[v].Position = x[v-1].Position + direction * L0;

            // correction vector for satisfying the constraint
            x[v].Correction = x[v].Position - x[v].Correction;
            // end solve constraint
        }
    }

    #pragma omp parallel for schedule(static) firstprivate(str) default(none)
    for(size_t s=0; s < this->hair.size(); s++)
    {
        const size_t nVert = str[s].size();
        Vertex* restrict x = str[s].data();

        #pragma omp simd aligned(x:Alignment)
        #pragma vector aligned
        for(size_t v=1; v < nVert; v++)
        {            
            x[v].Velocity = ((x[v].Position - x[v].OldPosition) / TimeStep);

            // correct the velocity with the correction vector computed for previous vertex
            // obviously this is not possible for the last particle, so add 0 in this case
            x[v].Velocity += (v+1>=this->hair[v].size()) ? vec3(0,0,0) : Damping * (-x[v+1].Correction / TimeStep); // (9)
            
            // uncomment this while commenting the very first OldPos assignment to get an interesting begin
//             x[v].OldPosition = x[v].Position;
        }
    }
}
