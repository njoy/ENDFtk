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
 *  @param[in] zaid        the ZA value of the material
 *  @param[in] awr         the atomic weight ratio
 *  @param[in] fissionq    the fission energy release data
 */
Type( int zaid, double awr, FissionEnergyReleaseData&& fissionq ) :
  BaseWithoutMT( zaid, awr ), data_( std::move( fissionq ) ) {}

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
       data_( readFissionEnergyReleaseData( begin, end, lineNumber, MAT,
                                            head.L2(), head.N2() ) ) {

    readSEND( begin, end, lineNumber, MAT, 1 );
  }
  catch( std::exception& e ) {

    Log::info( "Trouble while constructing section 458 of File 1 of Material {}",
               MAT );
    throw e;
  }
