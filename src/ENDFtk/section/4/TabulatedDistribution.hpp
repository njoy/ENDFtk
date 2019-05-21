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
   *  @brief Return the cosines values
   */
  auto cosines() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the distribution values
   */
  auto probabilities() const { return TabulationRecord::y(); }

  using TabulationRecord::NR;
  using TabulationRecord::NP;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
