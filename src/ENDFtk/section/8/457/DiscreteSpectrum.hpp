/**
 *  @class
 *  @brief Discrete spectrum information
 *
 *  The AverageDecayEnergies class is used to store the half life and the 
 *  average decay energies from MF8/MT457.
 *
 *  All quantities are given as values with associated uncertainties so these
 *  are handled as tuples.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class DiscreteSpectrum : protected ListRecord {

  /* members */

  /* auxiliary functions */
  #include "ENDFtk/section/8/457/DiscreteSpectrum/src/verifyNT.hpp"
  #include "ENDFtk/section/8/457/DiscreteSpectrum/src/generateList.hpp"
  #include "ENDFtk/section/8/457/DiscreteSpectrum/src/returnTuple.hpp"
    
public:

  /* constructor */
  #include "ENDFtk/section/8/457/DiscreteSpectrum/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of entries
   */
  int NT() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the decay chain responsible for this spectrum
   */
  double decayChain() const { return ListRecord::list()[0]; }

  /**
   *  @brief Return the discrete energy value and uncertainty
   */
  auto discreteEnergy() const {
      return std::tuple< double, double >( ListRecord::C1(),
                                           ListRecord::C2() ); }

  /**
   *  @brief Return the relative intensity and uncertainty
   */
  auto relativeIntensity() const {
      return std::tuple< double, double >( ListRecord::list()[2],
                                           ListRecord::list()[3] ); }

  /**
   *  @brief Transition type for beta and electron capture
   */
  double type() const { return ListRecord::list()[1]; }

  /**
   *  @brief Return the RIS value and its uncertainty
   *
   *  RIS is the internal pair formation coefficient (STYP=0.0) or the 
   *  positron intensity (STYP=2.0)
   */
  auto RIS() const { return this->returnTuple( 4 ); }

  /**
   *  @brief Return the RICC value and its uncertainty
   *
   *  RICC is the total internal conversion coefficient (STYP=0.0 only)
   */
  auto RICC() const { return this->returnTuple( 6 ); }

  /**
   *  @brief Return the RICK value and its uncertainty
   *
   *  RICK is the K shell internal conversion coefficient (STYP=0.0 only)
   */
  auto RICK() const { return this->returnTuple( 8 ); }

  /**
   *  @brief Return the RICL value and its uncertainty
   *
   *  RICL is the L shell internal conversion coefficient (STYP=0.0 only)
   */
  auto RICL() const { return this->returnTuple( 10 ); }

  using ListRecord::NC;
  using ListRecord::print;
};
