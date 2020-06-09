template<>
class Type< 3 > : protected Base {

  /* fields */
  TabulationRecord table;

public:

  /* constructor */
  #include "ENDFtk/section/3/src/ctor.hpp"

  /* get methods */
  double QM() const { return this->table.C1(); }
  double massDifferenceQValue() const { return this->QM(); }
  double QI() const { return this->table.C2(); }
  double reactionQValue() const { return this->QI(); }
  int LR() const { return this->table.L2(); }
  int complexBreakUp() const { return this->LR(); }
  long NR() const { return this->table.NR(); }
  long NP() const { return this->table.NP(); }

  auto interpolants() const { return this->table.interpolants(); }
  auto boundaries() const { return this->table.boundaries(); }
  auto energies() const { return this->table.x(); }
  auto crossSections() const { return this->table.y(); }

  long NC() const { return this->table.NC() + 1; }

  #include "ENDFtk/section/3/src/print.hpp"
    
  using Base::MT;
  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;
};

