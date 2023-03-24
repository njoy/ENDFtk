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
 *  @param[in] section   the MF7 MT2 section
 */
Type( section::Type< 7, 2 >&& section ) :
  Base( { std::move( section ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] section   the MF7 MT4 section
 */
Type( section::Type< 7, 4 >&& section ) :
  Base( { std::move( section ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] elastic     the MF7 MT2 section
 *  @param[in] inelastic   the MF7 MT4 section
 */
Type( section::Type< 7, 2 >&& elastic, section::Type< 7, 4 >&& inelastic ) :
  Base( { std::move( elastic ), std::move( inelastic ) } ) {}

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
      Iterator& begin, const Iterator& end, long& lineNumber ) :
  Base( division, begin, end, lineNumber ) {}
