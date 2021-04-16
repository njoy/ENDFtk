/**
 *  @brief Constructor for isotropic photon distributions
 *
 *  @param[in] mt              the MT number for the section
 *  @param[in] zaid            the material ZAID value
 *  @param[in] awr             the atomic weight ratio
 */
Type( int MT, double zaid, double awr ) :
  Base( zaid, awr, MT ),
  photons_() {}

/**
 *  @brief Constructor
 *
 *  @param[in] mt        the MT number for the section
 *  @param[in] zaid      the material ZAID value
 *  @param[in] awr       the atomic weight ratio
 *  @param[in] photons   the photon distribution data
 */
Type( int MT, double zaid, double awr,
      std::vector< PhotonDistribution >&& photons ) :
  Base( zaid, awr, MT ),
  photons_( std::move( photons ) ) {}

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
  try: Type( head.MT(), head.ZA(), head.AWR(),
             readPhotons( begin, end, lineNumber, head.MAT(), 14, head.MT(),
                          head.L1(), head.N2(), head.N1(), head.L2() ) ) {

    readSEND(begin, end, lineNumber, MAT, 14 );
  } catch( std::exception& e ) {

    Log::info
    ( "Encountered error while reading section {} of file 14 of material {}",
      head.MT(), MAT );
    throw;
  }
