/**
 *  @class
 *  @brief An angular distribution given as a tabulated function.
 *
 *  The TabulatedDistribution class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as a tabulated function.
 *
 *  See ENDF102, section 4.2.2 for more information.
 */
class TabulatedDistribution : protected TabulationRecord {

  /* auxiliary functions */

public:
  /* constructor */
  #include "ENDFtk/section/4/TabulatedDistribution/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double E() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the cosine values
   */
  auto MU() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const { return this->MU(); }

  /**
   *  @brief Return the distribution probabilities
   */
  auto F() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the distribution probabilities
   */
  auto probabilities() const { return this->F(); }

  using TabulationRecord::NR;
  using TabulationRecord::NP;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
