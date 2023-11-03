/**
 *  @class
 *  @brief Base class for a short-range Breit-Wigner and Reich-Moore resonance
 *         parameters and covariance data block
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ShortRangeBreitWignerReichMooreBlockBase : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/ShortRangeBreitWignerReichMooreBlockBase/src/verifySize.hpp"
  #include "ENDFtk/section/32/151/ShortRangeBreitWignerReichMooreBlockBase/src/generateList.hpp"

  auto column( unsigned int i ) const {

    return ListRecord::list() | ranges::views::take_exactly( 6 * this->NRB() )
                              | ranges::views::drop_exactly( i )
                              | ranges::views::stride( 6 );
  }

protected:

  /* constructor */
  #include "ENDFtk/section/32/151/ShortRangeBreitWignerReichMooreBlockBase/src/ctor.hpp"

  /**
   *  @brief Return the first width
   */
  auto G1() const { return ShortRangeBreitWignerReichMooreBlockBase::column( 2 ); }

  /**
   *  @brief Return the second width
   */
  auto G2() const { return ShortRangeBreitWignerReichMooreBlockBase::column( 3 ); }

  /**
   *  @brief Return the third width
   */
  auto G3() const { return ShortRangeBreitWignerReichMooreBlockBase::column( 4 ); }

  /**
   *  @brief Return the fourth width
   */
  auto G4() const { return ShortRangeBreitWignerReichMooreBlockBase::column( 5 ); }

  /**
   *  @brief Return the resonances
   */
  auto resonances() const {

    return ListRecord::list() | ranges::views::take_exactly( 6 * this->NRB() )
                              | ranges::views::chunk(6);
  }

public:

  /* get methods */

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double AWRI() const { return ListRecord::C1(); }

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double atomicWeightRatio() const { return this->AWRI(); }

  /**
   *  @brief Return the number of resonance parameters with covariance data
   *         (for each resonance)
   */
  int MPAR() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of resonance parameters with covariance data
   *         (for each resonance)
   */
  int numberParametersWithCovariances() const { return this->MPAR(); }

  /**
   *  @brief Return the number of resonances
   */
  int NRB() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of resonances
   */
  int numberResonances() const { return this->NRB(); }

  /**
   *  @brief Return the resonance energies
   */
  auto ER() const { return ShortRangeBreitWignerReichMooreBlockBase::column( 0 ); }

  /**
  *  @brief Return the resonance energies
   */
  auto resonanceEnergies() const { return this->ER(); }

  /**
   *  @brief Return the spin values
   */
  auto AJ() const { return ShortRangeBreitWignerReichMooreBlockBase::column( 1 ); }

  /**
   *  @brief Return the spin values
   */
  auto spinValues() const { return this->AJ(); }

  /**
   *  @brief Return the order of the covariance matrix
   */
  int NPARB() const { return this->MPAR() * this->NRB(); }

  /**
   *  @brief Return the order of the covariance matrix
   */
  int covarianceMatrixOrder() const { return this->NPARB(); }

  /**
   *  @brief Return the number of values in the upper triangular covariance matrix
   */
  int NVS() const {

    return this->covarianceMatrixOrder()
           * ( this->covarianceMatrixOrder() + 1 ) / 2 ;
  }

  /**
   *  @brief Return the number of resonances for this l value
   */
  int numberValues() const { return this->NVS(); }

  /**
   *  @brief Return the upper triangular covariance matrix
   */
  auto covarianceMatrix() const {

    return ListRecord::list() | ranges::views::drop_exactly( 6 * this->NRB() );
  }

  //! @todo provide convenience interface for the covariance data

  using ListRecord::NC;
  using ListRecord::print;
};
