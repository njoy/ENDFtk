class Subsection {
public:

  TabulationRecord table;

#include "ENDFtk/section/13/Subsection/src/ctor.hpp"

  double EG() const { return this->table.C1(); }
  double EK() const { return this->table.C2(); }
  int LP() const { return this->table.L1(); }
  int LF() const { return this->table.L2(); }
  auto energies() const { return this->table.x(); }
  auto crossSections() const { return this->table.y(); }

};
