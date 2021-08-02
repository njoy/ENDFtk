/**
 *  @brief Constructor
 *
 *  @param[in] mt             the MT number
 *  @param[in] zaid           the ZA  identifier
 *  @param[in] awr            the atomic mass ratio
 *  @param[in] boundaries     the interpolation range boundaries
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] x              the x values
 *  @param[in] h              the form factor or scattering function values
 */
Type( int mt, double zaid, double awr,
      std::vector< long >&& boundaries, std::vector< long >&& interpolants,
      std::vector< double >&& x, std::vector< double >&& h ) :
  Base( zaid, awr, mt ),
  table( 0.0, static_cast< int >( zaid ) / 1000, 0, 0,
         std::move( boundaries ), std::move( interpolants ),
         std::move( x ), std::move( h ) ) {}

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] head         the head record of the section
 *  @param[in] it           the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 */
template< typename Iterator >
Type ( HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try: Base( head, MAT, 27 ),
       table( begin, end, lineNumber, head.MAT(), 27, head.MT() ){
    readSEND(begin, end, lineNumber, MAT, 27 );
  }
  catch( std::exception& e ) {

    Log::info
    ( "Encountered error while reading section {} of file 27 of material {}",
      head.MT(), MAT );
    throw e;
  }
