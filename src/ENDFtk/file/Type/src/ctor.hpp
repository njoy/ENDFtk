/**
 *  @brief Constructor
 *
 *  @param[in] sections   the sections of the file
 */
Type( std::vector< Section >&& sections ) :
  sectionMap( fill( std::move( sections ) ) ) {}

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
template< typename BufferIterator >
Type( StructureDivision& division,
      BufferIterator& begin, const BufferIterator& end, long& lineNumber )
  try: sectionMap( read( division, begin, end, lineNumber ) ) {}
  catch ( std::exception& e ) {

    Log::info("Encountered error while generating file::Type<{}>", FileNumber );
    Log::info( "Line number: {}", lineNumber );
    throw e;
  }

/**
 *  @brief Constructor
 *
 *  @param[in] section    a section of the file
 *  @param[in] sections   zero or more additional sections of the file
 */
template < typename... Sections >
Type( Section&& section, Sections&&... sections ) :
  sectionMap( [] ( auto&&... sections ) {

    std::map< int, Section > map;
    auto insert_fn = insert{};
    int i[] = { (insert_fn( map, std::move( sections ) ), 0 )... };
    std::ignore = i;
    return map;
  }( std::move( section ), std::move( sections )... ) ) {}
