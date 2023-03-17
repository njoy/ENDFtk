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
 *  @param[in] sections   the sections of the file
 */
Type( std::vector< section::Type< FileNumber > >&& sections ) :
  Parent( std::move( sections ) ) {}

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
  Parent( division, begin, end, lineNumber ) {}
