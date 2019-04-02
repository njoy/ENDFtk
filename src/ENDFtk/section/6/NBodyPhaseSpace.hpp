class NBodyPhaseSpace : protected ControlRecord {

public:
  /* constructor */
  #include "ENDFtk/section/6/NBodyPhaseSpace/src/ctor.hpp"

  /* get methods */
  static constexpr int LAW() { return 6; }
  double APSX() const { return ControlRecord::C1(); }
  double totalMass() const { return this->APSX(); }
  int NPSX() const { return ControlRecord::N2(); }
  int numberParticles() const { return this->NPSX(); }
  using ControlRecord::NC;
  using ControlRecord::print;
};
