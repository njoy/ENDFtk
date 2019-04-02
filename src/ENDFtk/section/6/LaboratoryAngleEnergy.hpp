class LaboratoryAngleEnergy {
public:

  #include "ENDFtk/section/6/LaboratoryAngleEnergy/EnergyDistribution.hpp"
  #include "ENDFtk/section/6/LaboratoryAngleEnergy/AngularDistribution.hpp"

private:
  InterpolationSequenceRecord
    < LaboratoryAngleEnergy::AngularDistribution > data_;

public:
  /* constructor */
  #include "ENDFtk/section/6/LaboratoryAngleEnergy/src/ctor.hpp"

  /* get methods */
  static constexpr int LAW() { return 7; }
  long NR() const { return this->data_.tab2().NR(); }
  long NE() const { return this->data_.tab2().NZ(); }

  auto angularDistributions() const { return this->data_.records(); }

  auto interpolants() const { return this->data_.tab2().interpolants(); }
  auto boundaries() const { return this->data_.tab2().boundaries(); }

  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/6/LaboratoryAngleEnergy/src/print.hpp"
};
