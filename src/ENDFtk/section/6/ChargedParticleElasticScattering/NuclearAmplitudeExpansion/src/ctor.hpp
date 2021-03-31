//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
NuclearAmplitudeExpansion() = default;
#endif

/**
 *  @brief Private constructor
 */
NuclearAmplitudeExpansion( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLTP( this->L1() );
    verifySize( this->NW(), this->NL() );
}

private:

/**
 *  @brief Private constructor
 */
NuclearAmplitudeExpansion( double energy, int nl,
                           std::vector< double >&& list )
  try : NuclearAmplitudeExpansion( ListRecord( 0.0, energy, 1, 0,
                                               nl, std::move( list ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing nuclear amplitude "
               "expansion data (LAW=5 LTP=1)" );
    throw;
  }

public:

/**
 *  @brief Constructor
 *
 *  @param[in] energy    the incident energy value
 *  @param[in] nl        the Legendre order
 *  @param[in] b         the coefficients for expanding the nuclear scattering
 *                       cross section
 *  @param[in] a_real    the real component of the a coefficients
 *  @param[in] a_imag    the imaginary component of the a coefficients
 */
NuclearAmplitudeExpansion( double energy, int nl,
                           std::vector< double >&& b,
                           std::vector< double >&& a_real,
                           std::vector< double >&& a_imag )
  try : NuclearAmplitudeExpansion(
          ListRecord( 0.0, energy, 1, 0, nl,
                      generateList( nl, std::move ( b ),
                                    std::move ( a_real ),
                                    std::move ( a_imag ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing nuclear amplitude "
               "expansion data (LAW=5 LTP=1)" );
    throw;
  }

/**
 *  @brief Constructor
 *
 *  @param[in] energy    the incident energy value
 *  @param[in] nl        the Legendre order
 *  @param[in] b         the scattering coefficients (for expanding the nuclear
 *                       scattering cross section)
 *  @param[in] a         the interference coefficients (for expanding the
 *                       nuclear scattering amplitude matrix)
 */
NuclearAmplitudeExpansion( double energy, int nl,
                           std::vector< double >&& b,
                           std::vector< std::complex< double > >&& a )
  try : NuclearAmplitudeExpansion(
          ListRecord( 0.0, energy, 1, 0, nl,
                      generateList( nl, std::move ( b ),
                                    std::move ( a ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing nuclear amplitude "
               "expansion data (LAW=5 LTP=1)" );
    throw;
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
NuclearAmplitudeExpansion( Iterator& it, const Iterator& end, long& lineNumber,
                           int MAT, int MF, int MT )
  try : NuclearAmplitudeExpansion( ListRecord( it, end, lineNumber,
                                               MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading nuclear amplitude expansion "
               "data (LAW=5 LTP=1)" );
    throw;
  }
