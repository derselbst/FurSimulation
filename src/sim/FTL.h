
#include "ISimulation.h"

class FTL : public ISimulation
{
  FTL(Hair& h);
  
public:
  void addForce(vec3 f) override;
  void update() override;
};