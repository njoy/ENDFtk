class LaboratoryAngleEnergy {
public:

#include "ENDFtk/section/6/LaboratoryAngleEnergy/CosineOutgoingEnergyDistribution.hpp"
#include "ENDFtk/section/6/LaboratoryAngleEnergy/EnergyOutgoingCosineDistribution.hpp"

private:
  InterpolationSequenceRecord< LaboratoryAngleEnergy::EnergyOutgoingCosineDistribution > data_;

public:
  /* constructor */
#include "ENDFtk/section/6/LaboratoryAngleEnergy/src/ctor.hpp"

  /* get methods */
  long NR() const { return this->data_.tab2().NR(); }
  long NE() const { return this->data_.tab2().NZ(); }

  auto energies() const { return this->data_.records(); }

  auto interpolants() const { return this->data_.tab2().interpolants(); }
  auto boundaries() const { return this->data_.tab2().boundaries(); }

  long NC() const { return this->data_.NC(); }

#include "ENDFtk/section/6/LaboratoryAngleEnergy/src/print.hpp"
};
