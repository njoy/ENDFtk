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

  static void
  verifySize( int NPL, int MPAR, int NRB ) {

    if ( NPL < 1 ) {

      Log::error( "Encountered empty list" );
      Log::info( "NPL should be larger than zero and equal to 6 * NRB" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NRB value: {}", NRB );
      throw std::exception();
    }

    if ( ( MPAR < 1 ) || ( MPAR > 5 ) ) {

      Log::error( "Encountered illegal MPAR value" );
      Log::info( "NRB should be a value between 1 and 5" );
      Log::info( "NRB value: {}", MPAR );
      throw std::exception();
    }

    if ( NRB < 1 ) {

      Log::error( "Encountered illegal NRB value" );
      Log::info( "NRB should be larger than zero" );
      Log::info( "NRB value: {}", NRB );
      throw std::exception();
    }

    if ( NPL != 6 * NRB + MPAR * NRB * ( MPAR * NRB + 1 ) / 2 ) {

      Log::error( "Encountered inconsistent list size" );
      Log::info( "NPL must be equal to 6 * NRB + MPAR * NRB * ( MPAR * NRB + 1 ) / 2" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "MPAR value: {}", MPAR );
      Log::info( "NRB value: {}", NRB );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( std::vector< double >&& energies,
                std::vector< double >&& spins,
                std::vector< double >&& column1,
                std::vector< double >&& column2,
                std::vector< double >&& column3,
                std::vector< double >&& column4,
                std::vector< double >&& values ) {

    unsigned int nrb = energies.size();
    if ( ( spins.size() != nrb ) or ( column1.size() != nrb ) or
         ( column2.size() != nrb ) or ( column3.size() != nrb ) or
         ( column4.size() != nrb ) ) {

      Log::info( "The number of resonances and the resonance parameters are not "
                 "consistent" );
      Log::info( "NRS value: {}", nrb );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "spins.size(): {}", spins.size() );
      Log::info( "column1.size(): {}", column1.size() );
      Log::info( "column2.size(): {}", column2.size() );
      Log::info( "column3.size(): {}", column3.size() );
      Log::info( "column4.size(): {}", column4.size() );
      throw std::exception();
    }

    std::vector< double > list;
    for ( unsigned int i = 0; i < nrb; ++i ) {

      list.push_back( energies[i] );
      list.push_back( spins[i] );
      list.push_back( column1[i] );
      list.push_back( column2[i] );
      list.push_back( column3[i] );
      list.push_back( column4[i] );
    }
    list.insert( list.end(), values.begin(), values.end() );
    return list;
  }

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::take( 6 * this->NRB() )
                              | std20::views::drop( i )
                              | std23::views::stride( 6 );
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  ShortRangeBreitWignerReichMooreBlockBase( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifySize( this->NPL(), this->MPAR(), this->NRB() );
  }

protected:

  /* constructor */

  public:

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ShortRangeBreitWignerReichMooreBlockBase() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] mpar       the number of parameters with covariances
   *  @param[in] energies   the resonance energies (NRB values)
   *  @param[in] spins      the spin values (NRB values)
   *  @param[in] column1    the first width (NRB values)
   *  @param[in] column2    the second width (NRB values)
   *  @param[in] column3    the third width (NRB values)
   *  @param[in] column4    the fourth width (NRB values)
   *  @param[in] values     the values of the upper diagonal covaraince matrix
   */
  ShortRangeBreitWignerReichMooreBlockBase( int mpar,
                                            std::vector< double >&& energies,
                                            std::vector< double >&& spins,
                                            std::vector< double >&& column1,
                                            std::vector< double >&& column2,
                                            std::vector< double >&& column3,
                                            std::vector< double >&& column4,
                                            std::vector< double >&& values ) :
    // no try ... catch: exceptions will be handled in the derived class
    ShortRangeBreitWignerReichMooreBlockBase(
            ListRecord( 0., 0., mpar, 0, energies.size(),
                        generateList( std::move( energies ),
                                      std::move( spins ),
                                      std::move( column1 ),
                                      std::move( column2 ),
                                      std::move( column3 ),
                                      std::move( column4 ),
                                      std::move( values ) ) ) ) {}

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   */
  template< typename Iterator >
  ShortRangeBreitWignerReichMooreBlockBase(
          Iterator& it, const Iterator& end, long& lineNumber,
          int MAT, int MF, int MT ) :
     // no try ... catch: exceptions will be handled in the derived class
    ShortRangeBreitWignerReichMooreBlockBase( ListRecord( it, end, lineNumber,
                                                          MAT, MF, MT ) ) {}

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
