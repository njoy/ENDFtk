class EnergyDistribution : protected TabulationRecord {

public:
  /* constructor */
  #include "ENDFtk/section/6/LaboratoryAngleEnergy/EnergyDistribution/src/ctor.hpp"

  /* get methods */
  long NRP() const { return TabulationRecord::NR(); }
  long NEP() const { return TabulationRecord::NP(); }

  double cosine() const { return TabulationRecord::C2(); }

  auto energies() const { return TabulationRecord::x(); }
  auto probabilities() const { return TabulationRecord::y(); }

  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;

  using TabulationRecord::NC;
  using TabulationRecord::print;
};
