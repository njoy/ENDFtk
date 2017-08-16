class EnergyDependentFissionWidths : public Unresolved {
protected:
#include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/ctor.hpp"

  LIST list;

public:

  double NE() const { return this->list.NPL(); }
  const LIST& energyLIST() const { return this->list; }

};

