class Multiplicity : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/6/Multiplicity/src/ctor.hpp"

  /* get methods */
  using TabulationRecord::NP;
  using TabulationRecord::NR;
  double ZAP() const { return TabulationRecord::C1(); }
  double productIdentifier() const { return this->ZAP(); }
  double AWP() const { return TabulationRecord::C2(); }
  double productMassRatio() const { return this->AWP(); }
  int LIP() const { return TabulationRecord::L1(); }
  int productModifierFlag() const { return this->LIP(); }
  int LAW() const { return TabulationRecord::L2(); }
  auto energies() const { return TabulationRecord::x(); }
  auto multiplicities() const { return TabulationRecord::y(); }
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
