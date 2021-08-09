/**
 *  @brief Constructor
 *
 *  @param[in] mt             the MT number
 *  @param[in] zaid           the ZA  identifier
 *  @param[in] awr            the atomic mass ratio
 *  @param[in] epe            the subshell binding energy
 *  @param[in] efl            the fluorescence yield
 *  @param[in] boundaries     the interpolation range boundaries
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] energies       the energy values
 *  @param[in] xs             the cross section values
 */
Type( int mt, double zaid, double awr, double epe, double efl, 
      std::vector< long >&& boundaries, std::vector< long >&& interpolants,
      std::vector< double >&& energies, std::vector< double >&& xs ) :
  Base( zaid, awr, mt ),
  table( epe, efl, 0, 0,
         std::move( boundaries ), std::move( interpolants ),
         std::move( energies ), std::move( xs ) ) {}

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
  try: Base( head, MAT, 23 ),
       table( begin, end, lineNumber, head.MAT(), 23, head.MT() ){
    readSEND(begin, end, lineNumber, MAT, 23 );
  }
  catch( std::exception& e ) {

    Log::info
    ( "Encountered error while reading section {} of file 23 of material {}",
      head.MT(), MAT );
    throw e;
  }
