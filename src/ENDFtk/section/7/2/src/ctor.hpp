/** 
 *  @brief Constructor
 *
 *  @param[in] zaid   the material ZAID value
 *  @param[in] awr    the atomic weight ratio
 *  @param[in] law    the thermal scattering law
 */
Type( double zaid, double awr, ScatteringLaw&& law ) :
  BaseWithoutMT( zaid, awr ), law_( std::move( law ) ) {}

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
Type( HEAD& head,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT )
  try : BaseWithoutMT( head.ZA(), head.AWR() ),
        law_( readScatteringLaw( begin, end, lineNumber, MAT, 7, 2,
                                 head.L1() ) ) {
    readSEND(begin, end, lineNumber, MAT, 7 );
  } catch ( std::exception& e ) {
    Log::info( "Trouble while reading section 2 of File 7 of Material {}",
               MAT );
    throw e;
  }
