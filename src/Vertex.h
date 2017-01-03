 
struct Vertex
{
    Vertex(vec3 pos, float m);
    
    // whether animating this vertex is enabled or not
    bool IsEnabled;
    
    // indicates the mass of this particle
    float Mass;
    
    // holds the current position of the particle within space
    vec3 Position;
    
    // holds a force that will be applied during a subsequent simulation step of this particle
    vec3 Force;
    
    // we have to remember the velocity applied to this particle during last simulation step
    vec3 Velocity;
}