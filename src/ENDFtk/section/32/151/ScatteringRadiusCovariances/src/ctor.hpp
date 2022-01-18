/**
 *  @brief Constructor
 *
 *  @param[in] data          the NI-type data blocks
 */
ScatteringRadiusCovariances( std::vector< ExplicitCovariance >&& data ) :
  ni_( std::move( data ) ) {};

private:

/**
 *  @brief Private intermediate constructor
 *
 *  @param[in] data          the NI-type data blocks
 */
template< typename Iterator >
ScatteringRadiusCovariances( ControlRecord&& cont,
                             Iterator& begin,
                             const Iterator& end,
                             long& lineNumber,
                             int MAT, int MF, int MT ) :
  ScatteringRadiusCovariances( readSequence( begin, end, lineNumber,
                                             MAT, MF, MT, cont.N2() ) ) {}

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
ScatteringRadiusCovariances( Iterator& it, const Iterator& end, long& lineNumber,
                             int MAT, int MF, int MT )
  try : ScatteringRadiusCovariances(
          ControlRecord( it, end, lineNumber, MAT, MF, MT ),
          it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing covariance data "
               "for an energy dependent scattering radius" );
    throw;
  }
