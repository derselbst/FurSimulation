
#include "ISimulation.h"

/* Simulation class implementing the Follow The Leader (FTL) approach */
class FTL : public ISimulation
{
public:
    FTL(Hair& h);
    ~FTL() override;
    
    void update() override;
};
