/**
 *  @class
 *  @brief Covariance data for the R-matrix limited resonance data
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT CovarianceMatrix : protected ListRecord {

  /* auxiliary functions */

  static void
  verifySize( int NPL, int NPARB ) {

    if ( NPL < 1 ) {

      Log::error( "Encountered empty list" );
      Log::info( "NPL should be larger than zero and equal to NPARB * ( NPARB + 1 ) / 2" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NPARB value: {}", NPARB );
      throw std::exception();
    }

    if ( NPARB < 1 ) {

      Log::error( "Encountered illegal NPARB value" );
      Log::info( "NPARB should be larger than zero" );
      Log::info( "NPARB value: {}", NPARB );
      throw std::exception();
    }

    if ( NPL != NPARB * ( NPARB + 1 ) / 2 ) {

      Log::error( "Encountered inconsistent list size" );
      Log::info( "NPL must be equal to NPARB * ( NPARB + 1 ) / 2" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NPARB value: {}", NPARB );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( std::vector< double >&& values ) {

    return values;
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  CovarianceMatrix( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifySize( this->NPL(), this->NPARB() );
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  CovarianceMatrix() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] values     the values of the upper diagonal covaraince matrix
   */
  CovarianceMatrix( std::vector< double >&& values ) :
    // no try ... catch: exceptions will be handled in the derived class
    CovarianceMatrix( ListRecord(
                        0., 0., 0, 0,
                        [] ( unsigned int n ) {

                          return ( -1 + std::sqrt( 1 + 8 * n ) ) / 2;
                        }( values.size() ),
                        std::move( values ) ) ) {}

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
  CovarianceMatrix(
          Iterator& it, const Iterator& end, long& lineNumber,
          int MAT, int MF, int MT ) :
     // no try ... catch: exceptions will be handled in the derived class
    CovarianceMatrix( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}

  /* get methods */

  /**
   *  @brief Return the order of the covariance matrix
   */
  int NPARB() const { return ListRecord::N2(); }

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

    return ListRecord::list();
  }

  //! @todo provide convenience interface for the covariance data

  using ListRecord::NC;
  using ListRecord::print;
};
