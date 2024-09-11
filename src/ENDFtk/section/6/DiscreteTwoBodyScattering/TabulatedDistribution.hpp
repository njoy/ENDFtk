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
class ENDFTK_PYTHON_EXPORT TabulatedDistribution : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/TabulatedDistribution/src/verifyLANG.hpp"
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/TabulatedDistribution/src/verifySize.hpp"
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/TabulatedDistribution/src/generateList.hpp"

  /* workaround for the removal of range-v3 */

  // returning std20::views::single causes issues on the Python side
  // std::array< long, 1 > leads to assertion failure in Apple clang 14.5 so we
  // are using vectors of one element instead
  std::vector< long > interpolants_;
  std::vector< long > boundaries_;
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/TabulatedDistribution/src/generateArrays.hpp"

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

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::stride( 2 );
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

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 1 ) | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the distribution probabilities
   */
  auto probabilities() const {

    return this->F();
  }

  /**
   *  @brief Return the number of interpolation ranges
   */
  static constexpr long NR() { return 1; }

  /**
   *  @brief Return the number of interpolation ranges
   */
  static constexpr long numberInterpolationRegions() { return NR(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const {

    using namespace njoy::tools;
    return std20::views::all( this->interpolants_ );
  }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the boundaries
   */
  auto NBT() const {

    using namespace njoy::tools;
    return std20::views::all( this->boundaries_ );
  }

  /**
   *  @brief Return the boundaries
   */
  auto boundaries() const { return this->NBT(); }

  using ListRecord::NC;
  using ListRecord::print;
};
