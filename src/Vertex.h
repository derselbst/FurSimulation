#pragma once

#include <glm/glm.hpp>

typedef glm::vec3 vec3;

struct Vertex
{
    Vertex()
    {}
    
    Vertex(vec3 pos, float m) : Mass{m}, Position{pos}
    {}
    
    // whether animating this vertex is enabled or not
    bool IsEnabled{true};
    
    // indicates the mass of this particle
    float Mass{1.0f};
    
    // point in 3D space, where this particle is located
    // just like openGL we use a Right-Handed (Y-up) coordinate system here
    vec3 Position{0.0f,0.0f,0.0f};
    
    // holds a force that will be applied during a subsequent simulation step of this particle
    vec3 Force = vec3(0.0f,0.0f,0.0f);
    
    // we have to remember the velocity applied to this particle during last simulation step
    vec3 Velocity{0.0f,0.0f,0.0f};
};