class ChargedParticleElasticScattering {
public:

  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/SubSection.hpp"

private:
  InterpolationSequenceRecord< SubSection > data_;

public:
  /* constructor */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/src/ctor.hpp"

  /* get methods */
  static constexpr int LAW() { return 5; }
  double SPI() const { return this->data_.tab2().C1(); }
  double spin() const { return this->SPI(); }
  bool LIDP() const { return this->data_.tab2().L1(); }
  bool identicalParticles() const { return this->LIDP(); }
  long NR() const { return this->data_.tab2().NR(); }
  long NE() const { return this->data_.tab2().NZ(); }

  auto energies() const { return this->data_.records(); }

  auto interpolants() const { return this->data_.tab2().interpolants(); }
  auto boundaries() const { return this->data_.tab2().boundaries(); }

  long NC() const { return this->data_.NC(); }

#include "ENDFtk/section/6/ChargedParticleElasticScattering/src/print.hpp"
};
