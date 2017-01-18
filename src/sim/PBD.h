
#include "ISimulation.h"

class PBD : public ISimulation
{
public:
  PBD(Hair& h);
  ~PBD() override;
  
  void addForce(vec3 f) override;
  void update() override;
};
