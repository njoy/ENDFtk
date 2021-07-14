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
 *  @param[in] MT            the MT number for the section
 *  @param[in] zaid          the material ZAID value
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] production    the photon production data
 */
Type( int MT, double zaid, double awr, PhotonProduction&& production ) :
  Base( zaid, awr, MT ), photon_( std::move( production ) ) {}

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
  try : Base( head.ZA(), head.AWR(), head.MT() ),
        photon_( readPhotonProduction( begin, end, lineNumber,
                                       MAT, 12, head.MT(),
                                       head.L1(), head.N1() ) ) {
    readSEND( begin, end, lineNumber, MAT, 12 );
  } catch ( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 12 of Material {}",
               head.MT(), MAT );
    throw e;
  }
