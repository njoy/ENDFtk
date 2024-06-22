/**
 *  @class
 *  @brief An angular distribution given as a tabulated function.
 *
 *  The TabulatedDistribution class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as a tabulated function.
 *
 *  This component is similar to the MF4 component of the same name (with the
 *  exception that this gives tabulated values for each outgoing energy value as
 *  well).
 *
 *  See ENDF102, section 6.2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT TabulatedDistribution : protected Base {

  /* fields */
  int lang_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/TabulatedDistribution/src/checkLANG.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/TabulatedDistribution/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/TabulatedDistribution/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the representation type
   */
  int LANG() const { return this->lang_; }

  /**
   *  @brief Return the representation type
   */
  int representation() const { return this->LANG(); }

  using Base::E;
  using Base::incidentEnergy;
  using Base::ND;
  using Base::numberDiscreteEnergies;
  using Base::NA;
  using Base::numberAngularParameters;
  using Base::NW;
  using Base::NEP;
  using Base::numberSecondaryEnergies;
  using Base::EP;
  using Base::energies;
  using Base::F0;
  using Base::totalEmissionProbabilities;

  /**
   *  @brief Return the cosine values
   */
  auto MU() const {

    using namespace njoy::tools;
    return Base::list()
             | std23::views::chunk( 2 + this->NA() )
             | std20::views::transform(
                   std20::views::drop( 2 )
                       | std23::views::stride( 2 ) ); }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const { return this->MU(); }

  /**
   *  @brief Return the distribution probabilities
   */
  auto F() const {

    using namespace njoy::tools;
    return Base::list()
             | std23::views::chunk( 2 + this->NA() )
             | std20::views::transform(
                  [] ( const auto& array )
                     { return array | std20::views::drop( 3 )
                                    | std23::views::stride( 2 ); } );
  }

  /**
   *  @brief Return the distribution probabilities
   */
  auto probabilities() const { return this->F(); }

  using Base::NC;
  using Base::print;
};
