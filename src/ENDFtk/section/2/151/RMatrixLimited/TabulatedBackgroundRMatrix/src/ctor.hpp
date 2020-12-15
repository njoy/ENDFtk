private:

/**
 *  @brief Private intermediate constructor
 */
TabulatedBackGroundRMatrix( int index,
                            TabulationRecord&& real,
                            TabulationRecord&& imaginary ) :
  BaseBackGroundRMatrix( index ),
  real_( std::move( real ) ),
  imaginary_( std::move( imaginary ) ) {

    verify( this->real_, this->imaginary_ );
  }

public:

//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
TabulatedBackGroundRMatrix() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] index           the channel index
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] real            the real values of the tabulated rmatrix
 *  @param[in] imaginary       the real values of the tabulated rmatrix
 */
TabulatedBackGroundRMatrix( int index,
                            std::vector< long >&& boundaries,
                            std::vector< long >&& interpolants,
                            std::vector< double >&& energies,
                            std::vector< double >&& real,
                            std::vector< double >&& imaginary ) :
  TabulatedBackGroundRMatrix(
      index,
      TabulationRecord( 0.0, 0.0, 0, 0,
                        std::vector< long >( boundaries ),
                        std::vector< long >( interpolants ),
                        std::vector< double >( energies ),
                        std::move( real ) ),
      TabulationRecord( 0.0, 0.0, 0, 0,
                        std::move( boundaries ),
                        std::move( interpolants ),
                        std::move( energies ),
                        std::move( imaginary ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] index           the channel index
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] rmatrix         the complex tabulated rmatrix values
 */
TabulatedBackGroundRMatrix( int index,
                            std::vector< long >&& boundaries,
                            std::vector< long >&& interpolants,
                            std::vector< double >&& energies,
                            std::vector< std::complex< double > >&& rmatrix ) :
  TabulatedBackGroundRMatrix( index,
                              std::move( boundaries ),
                              std::move( interpolants ),
                              std::move( energies ),
                              extractReal( rmatrix ),
                              extractImaginary( rmatrix ) ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
TabulatedBackGroundRMatrix( int index,
                            TabulationRecord&& real,
                            Iterator& it, const Iterator& end, long& lineNumber,
                            int MAT, int MF, int MT ) :
  TabulatedBackGroundRMatrix(
      index, std::move( real ),
      TabulationRecord( it, end, lineNumber, MAT, MF, MT ) ) {}

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
TabulatedBackGroundRMatrix( ControlRecord&& record,
                            Iterator& it, const Iterator& end, long& lineNumber,
                            int MAT, int MF, int MT ) :
  TabulatedBackGroundRMatrix(
      record.L1(),
      TabulationRecord( it, end, lineNumber, MAT, MF, MT ),
      it, end, lineNumber, MAT, MF, MT ) {

    verifyLBK( record.L2() );
  }

public:
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
TabulatedBackGroundRMatrix( Iterator& it, const Iterator& end, long& lineNumber,
                            int MAT, int MF, int MT )
  try : TabulatedBackGroundRMatrix( ControlRecord( it, end, lineNumber,
                                                   MAT, MF, MT ),
                                    it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing channel background" );
    throw;
  }
