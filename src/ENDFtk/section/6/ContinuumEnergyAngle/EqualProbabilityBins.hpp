/**
 *  @class
 *  @brief Equal probability bins (LAW=1, LANG=3)
 *
 *  The EqualProbabilityBins class is used to represent an internal NJOY ENDF
 *  format for thermal scattering data. It is stored in MF6.
 *
 *  See NJOY2016 manual, section 7.4 for more information.
 */
class EqualProbabilityBins : protected ListRecord {

  /* type aliases */
  using StrideRange = decltype( ListRecord( 0., 0., 0, 0, 0, {} ).list()
                                  | ranges::view::stride( 0 ) );

  /* auxiliary functions */
  //#include "ENDFtk/section/6/ContinuumEnergyAngle/EqualProbabilityBins/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/EqualProbabilityBins/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the LANG value
   */
  static constexpr int LANG() { return 3; }

  /**
   *  @brief Return the incident energy
   */
  double EN() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy
   */
  double energy() const { return this->EN(); }

  /**
   *  @brief Return the number of secondary energy values
   */
  long NEP() const { return ListRecord::NPL() / ListRecord::N2(); }

  /**
   *  @brief Return the number of secondary energy values
   */
  long numberSecondaryEnergies() const { return this->NEP(); }

  /**
   *  @brief Return the secondary energy values
   */
  StrideRange EP() const {

    return ListRecord::list() | ranges::view::stride( ListRecord::N2() );
  }

  /**
   *  @brief Return the secondary energy values
   */
  StrideRange energies() const { return this->EP(); }

  using ListRecord::NC;
  using ListRecord::print;
};
