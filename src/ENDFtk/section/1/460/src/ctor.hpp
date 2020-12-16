/**
 *  @brief Constructor
 *
 *  @param[in] zaid       the ZA value of the material
 *  @param[in] awr        the atomic weight ratio
 *  @param[in] photons    the delayed photon data
 */
Type( double zaid, double awr, DelayedPhotonData&& photons ) :
  BaseWithoutMT( zaid, awr ), data_( std::move( photons ) ) {}

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] head         the head record of the section
 *  @param[in] begin        the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 */
template< typename Iterator >
Type ( const HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try: BaseWithoutMT( head, MAT, 1 ),
       data_( readPhotonData( begin, end, lineNumber,
                              MAT, head.L1(), head.N1() ) ) {

    readSEND( begin, end, lineNumber, MAT, 1 );
  }
  catch( std::exception& e ) {

    Log::info( "Trouble while reading section 460 of File 1 of Material {}",
               MAT );
    throw e;
  }
