//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  TabulationRecord() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] C1             the double in column 1 on line 1
 *  @param[in] C2             the double in column 2 on line 1
 *  @param[in] L1             the integer in column 3 on line 1
 *  @param[in] L2             the integer in column 4 on line 1
 *  @param[in] boundaries     the interpolation range boundaries
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] x              the x values
 *  @param[in] y              the y values
 */
TabulationRecord ( double C1, double C2, long L1, long L2,
                    std::vector< long >&& boundaries,
                    std::vector< long >&& interpolants,
                    std::vector< double >&& x,
                    std::vector< double >&& y )
  try : InterpolationBase( C1, C2, L1, L2, std::move( boundaries ),
                           std::move( interpolants ) ),
                           xValues( std::move( x ) ),
                           yValues( std::move( y ) ) {

    verifyXValuesAreSorted( this->xValues );
    verifyVectorSizes( this->xValues, this->yValues );
    verifyNP( this->boundaries().back(), this->xValues.size() );
  }
  catch ( std::exception& e ) {
    Log::info( "Error encountered while constructing TAB1 record" );
    throw e;
  }

/**
 *  @brief Constructor
 *
 *  @param[in] C1         the double in column 1 on line 1
 *  @param[in] C2         the double in column 2 on line 1
 *  @param[in] L1         the integer in column 3 on line 1
 *  @param[in] L2         the integer in column 4 on line 1
 *  @param[in] regions    the interpolation regions
 *  @param[in] points     the x,y points
 */
TabulationRecord ( double C1, double C2, long L1, long L2,
                   std::tuple< std::vector< long >,
                               std::vector< long > >&& regions,
                   std::tuple< std::vector< double >,
                               std::vector< double > >&& points ) :
  TabulationRecord( C1, C2, L1, L2,
                    std::move( std::get<0>(regions) ),
                    std::move( std::get<1>(regions) ),
                    std::move( std::get<0>(points) ),
                    std::move( std::get<1>(points) ) ){}

private:

/**
 *  @brief Private constructor
 */
TabulationRecord
( InterpolationBase&& interpolation,
  std::tuple< std::vector< double >, std::vector< double > >&& points ) :
  InterpolationBase( std::move( interpolation ) ),
  xValues( std::move( std::get<0>( points ) ) ),
  yValues( std::move( std::get<1>( points ) ) ) {}

/**
 *  @brief Private constructor
 */
template< typename Iterator >
TabulationRecord
( InterpolationBase&& interpolation,
  Iterator& it, const Iterator& end, long& lineNumber,
  int MAT, int MF, int MT  ) :
  TabulationRecord( std::move( interpolation ),
                    readPairs( interpolation.N2(), it, end,
                               lineNumber, MAT, MF, MT ) ) {}

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
TabulationRecord( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
  try: TabulationRecord( InterpolationBase( it, end, lineNumber, MAT, MF, MT ),
                         it, end, lineNumber, MAT, MF, MT ) {}
  catch ( IllegalN2& e ) {
    Log::error( "Illegal NP value encountered" );
    Log::info( "NP (or number of pairs) must be greater than or equal to 1" );
    Log::info( "NP value: {}", e.n2 );
    Log::info( "Error encountered while parsing TAB1 record" );
    throw std::exception();
  }
  catch ( InconsistentN2& e ) {
    Log::error( "Inconsistent value for NP" );
    Log::info( "Expected {} as the largest index but found {}", e.n2, e.index );
    Log::info( "Error encountered while parsing TAB1 record" );
    throw std::exception();
  }
  catch ( int nPosition ){
    Log::info( "Error in position {}", nPosition );
    Log::info( "Error encountered while parsing TAB1 record" );
    throw std::exception();
  }
  catch ( std::exception& e ) {
    Log::info( "Error encountered while parsing TAB1 record" );
    throw e;
  }
