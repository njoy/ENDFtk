template<>
class Type< 8, 457 > : protected Base {

public:

  #include "ENDFtk/section/8/457/AverageDecayEnergies.hpp"

private:

  /* fields */
  unsigned int lis_;
  unsigned int liso_;
  bool nst_;

  AverageDecayEnergies energies_;
//  DecayModes modes_;
//  std::vector< DecaySpectrum > spectra_;

  /* auxiliary functions */

public:

  /* constructor */
//  #include "ENDFtk/section/8/457/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the excited state number
   */
  unsigned int excitedState() const { return this->lis_; }

  /**
   *  @brief Return the isomeric state number
   */
  unsigned int isomericState() const { return this->liso_; }

  /**
   *  @brief Return the stability flag
   */
  bool isStable() const { return this->nst_; }

  /**
   *  @brief Return the half life and its uncertainty
   */
  auto halfLife() const {

      return this->energies_.halfLife();
  }

  /**
   *  @brief Return the half life and decay energy information
   */
  const AverageDecayEnergies& averageDecayEnergies() const {

      return this->energies_;
  }

  #include "ENDFtk/section/8/457/src/NC.hpp"

  #include "ENDFtk/section/8/457/src/print.hpp"

  using Base::MT;
  using Base::ZA;
  using Base::atomicWeightRatio;
  using Base::AWR;
};
