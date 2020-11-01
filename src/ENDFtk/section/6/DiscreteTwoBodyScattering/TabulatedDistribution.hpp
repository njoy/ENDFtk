/**
 *  @class
 *  @brief An angular distribution given as a tabulated function.
 *
 *  The TabulatedDistribution class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as a tabulated function.
 *
 *  This component is similar to the MF4 component of the same name (with the
 *  exception that this is ListRecord based).
 *
 *  See ENDF102, section 6.2.4 for more information.
 */
class TabulatedDistribution : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/TabulatedDistribution/src/verifyLANG.hpp"
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/TabulatedDistribution/src/verifySize.hpp"
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/TabulatedDistribution/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/TabulatedDistribution/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the interpolation type for this distribution (12 or 14)
   */
  int LANG() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of values (cosine and probabilities)
   */
  long NW() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the number of cosine values
   */
  long NL() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of cosine values
   */
  long numberCosineValues() const { return this->NL(); }

  /**
   *  @brief Return the cosine values
   */
  auto MU() const {

    return ListRecord::list() | ranges::view::stride( 2 );
  }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const {

    return this->MU();
  }

  /**
   *  @brief Return the distribution probabilities
   */
  auto F() const {

    return ranges::view::drop_exactly( ListRecord::list(), 1 )
             | ranges::view::stride( 2 );
  }

  /**
   *  @brief Return the distribution probabilities
   */
  auto probabilities() const {

    return this->F();
  }

  using ListRecord::NC;
  using ListRecord::print;
};
