//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Type() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] zaid            the ZA value of the material
 *  @param[in] awr             the atomic weight ratio
 *  @param[in] multiplicity    the multiplicity data
 */
Type( double zaid, double awr, Multiplicity&& multiplicity ) :
  BaseWithoutMT( zaid, awr ), data_( std::move( multiplicity ) ) {}

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
       data_( std::move( readMultiplicity( begin, end, lineNumber,
                                           MAT, 1, head.MT(), head.L2() ) ) ) {
    readSEND( begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 1 of Material {}",
               head.MT(), MAT );
    throw e;
  }
