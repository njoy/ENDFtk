private:

/**
 *  @brief Private intermediate constructor
 *
 *  The number of entries in the temperatures array is checked against the
 *  temperature dependence flag LT (the L1 value on the TabulationRecord).
 */
ScatteringFunction( TabulationRecord&& alphas,
                    std::vector< ListRecord >&& temperatures ) :
  alphas_( std::move( alphas ) ), temperatures_( std::move( temperatures ) ) {

  this->generateSandT();
  if ( this->NT() != 1 ) {
    verifyBetaValues( this->beta(),
                      this->temperatures_ |
                          njoy::tools::std20::views::transform(
                              [] ( const auto& v )
                                 { return v.C2(); } ) );
  }
}

public:

ScatteringFunction( const ScatteringFunction& f ) :
  alphas_( f.alphas_ ), temperatures_( f.temperatures_ ) {

  this->generateSandT();
}

ScatteringFunction( ScatteringFunction&& f ) :
  alphas_( std::move( f.alphas_ ) ), temperatures_( std::move( f.temperatures_ ) ) {

  this->generateSandT();
}


/**
 *  @brief Constructor (multiple temperatures)
 *
 *  The size of the various arrays is checked for consistency where appropriate.
 *
 *  @param[in] beta           the beta value for which data will be given
 *  @param[in] boundaries     the interpolation range boundaries for S(a,beta)
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] temperatures   the temperatures (NT values)
 *  @param[in] li             the temperature interpolation flags (NT-1 values)
 *  @param[in] alphas         the alpha values (NA values)
 *  @param[in] sab            the thermal scattering values (NT arrays of NA
 *                            values)
 */
ScatteringFunction( double beta,
                    std::vector< long >&& boundaries,
                    std::vector< long >&& interpolants,
                    std::vector< double >&& temperatures,
                    std::vector< long >&& li,
                    std::vector< double >&& alphas,
                    std::vector< std::vector< double > >&& sab )
  try : ScatteringFunction(
            TabulationRecord( temperatures[0], beta,
                              temperatures.size() - 1, 0,
                              std::move( boundaries ),
                              std::move( interpolants ),
                              std::move( alphas ),
                              std::move( sab[0] ) ),
            generateTemperatures( beta,
                                  std::move( temperatures ),
                                  std::move( li ),
                                  std::move( sab ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing S(a,b) data for a given "
               "beta value" );
    throw;
  }

/**
 *  @brief Constructor (single temperature)
 *
 *  The size of the various arrays is checked for consistency where appropriate.
 *
 *  @param[in] temperature    the temperature
 *  @param[in] beta           the beta value for which data will be given
 *  @param[in] boundaries     the interpolation range boundaries for S(a,beta)
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] alphas         the alpha values (NA values)
 *  @param[in] sab            the thermal scattering values (NA values)
 */
ScatteringFunction( double temperature, double beta,
                    std::vector< long >&& boundaries,
                    std::vector< long >&& interpolants,
                    std::vector< double >&& alphas,
                    std::vector< double >&& sab )
  try : ScatteringFunction( TabulationRecord( temperature, beta, 0, 0,
                                              std::move( boundaries ),
                                              std::move( interpolants ),
                                              std::move( alphas ),
                                              std::move( sab ) ), {} ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing S(a,b) data for a given "
               "beta value" );
    throw;
  }

private:
/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
ScatteringFunction( TabulationRecord&& alphas,
                    Iterator& begin,
                    const Iterator& end,
                    long& lineNumber,
                    int MAT,
                    int MF,
                    int MT ) :
  ScatteringFunction( std::move( alphas ),
                      readSequence< ListRecord >( begin, end, lineNumber,
                                                  MAT, MF, MT, alphas.L1() ) ) {}

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
ScatteringFunction( Iterator& begin,
                    const Iterator& end,
                    long& lineNumber,
                    int MAT,
                    int MF,
                    int MT )
  try : ScatteringFunction( TabulationRecord( begin, end, lineNumber,
                                              MAT, MF, MT ),
                            begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing S(a,b) data for a given "
               "beta value" );
    throw;
  }

ScatteringFunction& operator=( const ScatteringFunction& base ) {

  if ( this != &base ) {

    this->alphas_ = base.alphas_;
    this->temperatures_ = base.temperatures_;
    this->generateSandT();
  }
  return *this;
}

ScatteringFunction& operator=( ScatteringFunction&& base ) {

  if ( this != &base ) {

    this->alphas_ = std::move( base.alphas_ );
    this->temperatures_ = std::move( base.temperatures_ );
    this->generateSandT();
  }
  return *this;
}
