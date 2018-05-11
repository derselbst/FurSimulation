
#include "ISimulation.h"

/* Simulation class implementing the Position Based Dynamics (PDB) approach */
class PBD : public ISimulation
{
public:
    PBD(Hair& h);
    ~PBD() override;
    void update() override;
};
