/**
 *  @class
 *  @brief Internal NJOY thermal scattering data (LAW=1, LANG=3)
 *
 *  The ThermalScatteringData class is used to represent an internal NJOY ENDF
 *  format for thermal scattering data. It is stored in MF6.
 *
 *  See NJOY2016 manual, section 7.4 for more information.
 */
class ThermalScatteringData : protected ListRecord {

  /* type aliases */
  using Range = decltype( std::declval< ListRecord >().list() );
  using StrideRange = decltype( std::declval< Range >() | ranges::view::stride( 0 ) );
  using DropStrideRange = decltype( std::declval< Range >() | ranges::view::drop_exactly( 0 ) | ranges::view::stride( 0 ) );

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
  Range data() const { return ListRecord::list(); }

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
  int numberEnergies() const { return this->NEP(); }

  /**
   *  @brief Return the LTT flag (the format representation type)
   */
  int LTT() const { return this->data().front() == this->incidentEnergy() ? 6 : 5; }

  /**
   *  @brief Return the number of energy points
   */
  StrideRange energies() const {

    return this->data() | ranges::view::stride( this->N2() );
  }

  /**
   *  @brief Return second value for every energy
   */
  DropStrideRange PP() const {

    return this->data() | ranges::view::drop_exactly( 1 )
                        | ranges::view::stride( this->N2() );
  }

  /**
   *  @brief Return the cosines
   */
  auto cosines() const {

    return this->data()
             | ranges::view::chunk( this->N2() )
             | ranges::view::transform(
                   [] ( const auto& array )
                      { return array | ranges::view::drop_exactly( 2 ); } );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
