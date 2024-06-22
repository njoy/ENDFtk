/**
 *  @class
 *  @brief Base class for a short-range Breit-Wigner and Reich-Moore resonance
 *         parameters and covariance data block
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ShortRangeBreitWignerReichMooreBlockBase :
  protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/ShortRangeBreitWignerReichMooreBlockBase/src/verifySize.hpp"
  #include "ENDFtk/section/32/151/ShortRangeBreitWignerReichMooreBlockBase/src/generateList.hpp"

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::take( 6 * this->NRB() )
                              | std20::views::drop( i )
                              | std23::views::stride( 6 );
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

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::take( 6 * this->NRB() )
                              | std23::views::chunk( 6 );
  }

public:

  /* get methods */

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

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 6 * this->NRB() );
  }

  //! @todo provide convenience interface for the covariance data

  using ListRecord::NC;
  using ListRecord::print;
};
