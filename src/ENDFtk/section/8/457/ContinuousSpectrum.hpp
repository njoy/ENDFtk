/**
 *  @class
 *  @brief Continuous decay spectrum
 *
 *  The ContinuousSpectrum class is used to represent the continuous part of the
 *  spectrum for a specific decay radiation type (designated by STYP) of
 *  MF8/MT457.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class ContinuousSpectrum : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/8/457/ContinuousSpectrum/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the decay chain responsible for this spectrum
   */
  double RTYP() const { return TabulationRecord::C1(); }

  /**
   *  @brief Return the decay chain responsible for this spectrum
   */
  double decayChain() const { return this->RTYP(); }

  /**
   *  @brief Return the energy values
   */
  AllRange< double > E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energy values
   */
  AllRange< double > energies() const { return this->E(); }

  /**
   *  @brief Return the spectral values
   */
  AllRange< double > RP() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the spectral values
   */
  AllRange< double > spectralValues() const { return this->RP(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
