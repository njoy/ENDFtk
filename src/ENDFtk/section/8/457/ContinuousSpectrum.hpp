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
class ENDFTK_PYTHON_EXPORT ContinuousSpectrum : protected TabulationRecord {

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
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the spectral values
   */
  auto RP() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the spectral values
   */
  auto spectralValues() const { return this->RP(); }

  using TabulationRecord::NP;
  using TabulationRecord::numberPoints;
  using TabulationRecord::NR;
  using TabulationRecord::numberInterpolationRegions;
  using TabulationRecord::INT;
  using TabulationRecord::interpolants;
  using TabulationRecord::NBT;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
