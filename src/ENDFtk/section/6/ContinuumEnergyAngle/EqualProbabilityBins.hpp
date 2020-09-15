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
  using Range = decltype( std::declval< ListRecord >().list() );

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
   *  @brief Return the data contained in this component
   */
  Range data() const { return ListRecord::list(); }

  /**
   *  @brief Return the data contained in this component
   */
  int NW() const { return ListRecord::NPL(); }

  using ListRecord::N2;
  using ListRecord::NC;
  using ListRecord::print;
};
