/**
 *  @class
 *  @brief Charged particle elastic scattering data for secondary
 *         particles (LAW=5)
 *
 *  The ChargedParticleElasticScattering class is used to represent the
 *  charged particle law=5 data of MF6.
 *
 *  See ENDF102, section 6.2.7 for more information.
 */
class ChargedParticleElasticScattering {

public:

  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference.hpp"

  using Variant = std::variant< NuclearAmplitudeExpansion, // LTP=1
                                LegendreCoefficients,      // LTP=2
                                NuclearPlusInterference >; // LTP>2

private:

  /* fields */
  InterpolationSequenceRecord< Variant > data_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/src/readSequence.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the LAW flag for continuum energy-angle data
   */
  static constexpr int LAW() { return 5; }

  /**
   *  @brief Return the spin of the particle
   */
  double SPI() const { return this->data_.tab2().C1(); }

  /**
   *  @brief Return the spin of the particle
   */
  double spin() const { return this->SPI(); }

  /**
   *  @brief Return whether or not the particles are identical
   */
  bool LIDP() const { return this->data_.tab2().L1(); }

  /**
   *  @brief Return whether or not the particles are identical
   */
  bool identicalParticles() const { return this->LIDP(); }

  /**
   *  @brief Return the number of interpolation ranges on the incident
   *         energy axis
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of incident energy values
   */
  long NE() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the subsections, one for each incident energy
   */
  auto subsections() const { return this->data_.records(); }

  /**
   *  @brief Return interpolation type for each range on the incident
   *         energy grid
   */
  auto interpolants() const { return this->data_.tab2().interpolants(); }

  /**
   *  @brief Return interpolation boundaries for the incident energy grid
   */
  auto boundaries() const { return this->data_.tab2().boundaries(); }

  /**
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/6/ChargedParticleElasticScattering/src/print.hpp"
};
