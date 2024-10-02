/**
 *  @class
 *  @brief Internal NJOY thermal scattering data (LAW=1, LANG=3)
 *
 *  The ThermalScatteringData class is used to represent an internal NJOY ENDF
 *  format for thermal scattering data. It is stored in MF6.
 *
 *  See NJOY2016 manual, section 7.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT ThermalScatteringData : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/ThermalScatteringData/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/ThermalScatteringData/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the LANG value
   */
  static constexpr int LANG() { return 3; }

  /**
   *  @brief Return the representation type
   */
  int representation() const { return this->LANG(); }

  /**
   *  @brief Return the incident energy
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the data contained in this component
   */
  auto data() const { return ListRecord::list(); }

  /**
   *  @brief Return the data contained in this component
   */
  int NW() const { return ListRecord::NPL(); }

  using ListRecord::N2;

  /**
   *  @brief Return the number of energy points
   */
  int NEP() const { return this->NW() / this->N2(); }

  /**
   *  @brief Return the number of energy points
   */
  int numberSecondaryEnergies() const { return this->NEP(); }

  /**
   *  @brief Return the LTT flag (the format representation type)
   */
  int LTT() const { return this->data().front() == this->incidentEnergy() ? 6 : 5; }

  /**
   *  @brief Return the number of energy points
   */
  auto EP() const {

    using namespace njoy::tools;
    return this->data() | std23::views::stride( this->N2() );
  }

  /**
   *  @brief Return the number of energy points
   */
  auto energies() const { return this->EP(); }

  /**
   *  @brief Return second value for every energy
   */
  auto PP() const {

    using namespace njoy::tools;
    return this->data() | std20::views::drop( 1 )
                        | std23::views::stride( this->N2() );
  }

  /**
   *  @brief Return the cosine values
   */
  auto MU() const {

    using namespace njoy::tools;
    return this->data()
             | std23::views::chunk( this->N2() )
             | std20::views::transform(
                   [] ( const auto& array )
                      { return array | std20::views::drop( 2 ); } );
  }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const { return this->MU();  }

  using ListRecord::NC;
  using ListRecord::print;
};
