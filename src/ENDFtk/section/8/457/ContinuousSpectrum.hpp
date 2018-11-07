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
  double decayChain() const { return TabulationRecord::C1(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  auto energies() const { return TabulationRecord::x(); }
  auto spectralValues() const { return TabulationRecord::y(); }
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
