/**
 *  @brief Constructor
 *
 *  @param[in] zaid            the ZA value of the material
 *  @param[in] awr             the atomic weight ratio
 *  @param[in] constants       the decay constant data
 *  @param[in] multiplicity    the multiplicity data
 */
Type( double zaid, double awr, DecayConstantData&& constants,
      Multiplicity&& multiplicity ) :
  BaseWithoutMT( zaid, awr ), lambda_( std::move( constants ) ),
  nubar_( std::move( multiplicity ) ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
Type( double zaid, double awr, DecayConstantData&& constants,
      Iterator& begin, const Iterator& end, long& lineNumber,
      int MAT, int LNU ) :
  Type( zaid, awr, std::move( constants ),
        readMultiplicity( begin, end, lineNumber, MAT, 1, 455, LNU ) ) {}

public:

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
Type( const HEAD& head,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT )
  try: Type( head.ZA(), head.AWR(),
             readDecayConstantData( begin, end, lineNumber,
                                    MAT, 1, 455, head.L1() ),
             begin, end, lineNumber, MAT, head.L2() ) {

    readSEND( begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {

    Log::info( "Trouble while constructing section 455 of File 1 of Material {}",
               MAT );
    throw e;
  }
