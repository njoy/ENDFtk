/**
 *  @brief Constructor
 *
 *  @param[in] legendre    the legendre distributions
 *  @param[in] tabulated   the tabulated distributions
 */
MixedDistributions( LegendreDistributions&& legendre,
                    TabulatedDistributions&& tabulated ) :
  legendre_( std::move( legendre ) ), tabulated_( std::move( tabulated ) ) {

    verifyBoundary(
      this->legendre_.angularDistributions().back().incidentEnergy(),
      this->tabulated_.angularDistributions().front().incidentEnergy() );
    this->generateArrays();
  }

private:

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
MixedDistributions( LegendreDistributions&& legendre,
                    Iterator& begin,
                    const Iterator& end,
                    long& lineNumber,
                    int MAT,
                    int MF,
                    int MT ) :
  MixedDistributions( std::move( legendre ),
                      TabulatedDistributions( begin, end, lineNumber,
                                              MAT, MF, MT ) ) {}

public:

MixedDistributions( const MixedDistributions& base ) :
  legendre_( base.legendre_ ), tabulated_( base.tabulated_ ) {

  this->generateArrays();
}

MixedDistributions( MixedDistributions&& base ) :
  legendre_( std::move( base.legendre_ ) ), tabulated_( std::move( base.tabulated_ ) ) {

  this->generateArrays();
}

MixedDistributions& operator=( const MixedDistributions& base ) {

  if ( this != &base ) {

    this->legendre_ = base.legendre_;
    this->tabulated_ = base.tabulated_;
    this->generateArrays();
  }
  return *this;
}

MixedDistributions& operator=( MixedDistributions&& base ) {

  if ( this != &base ) {

    this->legendre_ = std::move( base.legendre_ );
    this->tabulated_ = std::move( base.tabulated_ );
    this->generateArrays();
  }
  return *this;
}

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
MixedDistributions( Iterator& begin,
                    const Iterator& end,
                    long& lineNumber,
                    int MAT,
                    int MF,
                    int MT )
  try : MixedDistributions( LegendreDistributions( begin, end, lineNumber,
                                                   MAT, MF, MT ),
                            begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( const std::exception& e ) {

    Log::info( "Error encountered while constructing a mixed "
               "angular distribution" );
    throw;
  }
