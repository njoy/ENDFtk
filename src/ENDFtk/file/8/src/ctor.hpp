//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Type() = default;
#endif

/**
 *  @brief Constructor (radioactive decay data)
 *
 *  @param[in] section   the MF8 MT457 section
 */
Type( section::Type< 8, 457 >&& section ) :
  Base( { std::move( section ) } ) {}

/**
 *  @brief Constructor (direct fission yield)
 *
 *  @param[in] section   the MF8 MT454 section
 */
Type( section::Type< 8, 454 >&& section ) :
  Base( { std::move( section ) } ) {}

/**
 *  @brief Constructor (cumulative fission yield)
 *
 *  @param[in] section   the MF8 MT459 section
 */
Type( section::Type< 8, 459 >&& section ) :
  Base( { std::move( section ) } ) {}

/**
 *  @brief Constructor (fission yields)
 *
 *  @param[in] direct       the MF8 MT454 section
 *  @param[in] cumulative   the MF8 MT459 section
 */
Type( section::Type< 8, 454 >&& direct, section::Type< 8, 459 >&& cumulative ) :
  Base( { std::move( direct ), std::move( cumulative ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] sections   the sections of the file
 */
Type( std::vector< SectionVariant >&& sections ) :
  Base( std::move( sections ) ) {}

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] division     the first HEAD record of the section
 *  @param[in] it           the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 */
template< typename Iterator >
Type( StructureDivision& division,
      Iterator& begin, const Iterator& end, long& lineNumber ) : Base() {

  //! @todo remove this and set fields and auxiliary functions in Base to private
  try {

    int MT = division.tail.MT();
    if ( ( division.tail.MT() == 454 ) ||
         ( division.tail.MT() == 457 ) ||
         ( division.tail.MT() == 459 ) ) {

      this->sections_ = read( division, begin, end, lineNumber );
    }
    else {

      int MF = 8;
      if ( division.tail.MF() == MF ) {

        Log::info( "Found unsupported section MF{} MT{} - skipping file", MF, MT );

        while ( division.tail.MF() == MF ) {

          Tail tail( division.tail.MAT(), division.tail.MF(), division.tail.MT() );
          int MT = tail.MT();
          while ( tail.MT() == MT ) {

            Text( begin, end );
            tail = Tail( begin, end, lineNumber );
          }
          division = StructureDivision( begin, end, lineNumber );
        }
      }
      this->verifyFEND( division, lineNumber );
    }
  }
  catch ( std::exception& e ) {

    Log::info("Error while reading File 8");
    throw e;
  }
}
