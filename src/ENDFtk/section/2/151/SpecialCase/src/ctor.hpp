/**
 *  @brief Constructor
 *
 *  @param[in] spi   the target spin
 *  @param[in] ap    the scattering radius
 */
SpecialCase( double spi, double ap ) :
    // no need for a try ... catch: nothing can go wrong here
    spi_( spi ), ap_( ap ) {}

private:
/**
 *  @brief Private intermediate constructor
 */
SpecialCase( ControlRecord&& cont ) :
  SpecialCase( cont.C1(), cont.C2() ) {}

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
SpecialCase( Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT )
  try : SpecialCase( ControlRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing the special case without "
               "resonance parameters" );
    throw;
  }
