
#include "ISimulation.h"

class FTL : public ISimulation
{
public:
  FTL(Hair& h);
  ~FTL() override;
  
  void addForce(vec3 f) override;
  void update() override;
};