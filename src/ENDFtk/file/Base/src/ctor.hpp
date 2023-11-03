//! @todo pybind11 variant needs default constructor workaround
//#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Base() = default;
//#endif

/**
 *  @brief Constructor
 *
 *  @param[in] sections   the sections of the file
 */
Base( std::vector< Section >&& sections ) :
  sections_( fill( std::move( sections ) ) ) {}

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
Base( StructureDivision& division,
      Iterator& begin, const Iterator& end, long& lineNumber )
  try: sections_( read( division, begin, end, lineNumber ) ) {}
  catch ( std::exception& e ) {

    Log::info("Encountered error while reading file::Type<{}>", this->MF() );
    Log::info( "Line number: {}", lineNumber );
    throw e;
  }
