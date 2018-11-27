/**
 *  @class
 *  @brief Partial probability for a given distribution
 *
 *  The PartialProbability class is used to provide the probability 
 *  that the associated distribution can be used at a given incident 
 *  energy.
 *
 *  See ENDF102, section 5 for more information.
 */
class PartialProbability : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/5/PartialProbability/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  int LF() const { return TabulationRecord::L2(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the probability values
   */
  auto probabilities() const { return TabulationRecord::y(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
