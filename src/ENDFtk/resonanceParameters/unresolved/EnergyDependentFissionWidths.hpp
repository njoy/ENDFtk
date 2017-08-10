class EnergyDependentFissionWidths : public Unresolved {
protected:
#include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/ctor.hpp"

  LIST list;
  int ne; // Number of energy points at which there are energy-dependent widths

public:

  double NE() const { return this->ne; }
  auto energyLIST() const { return this->list; }

};

