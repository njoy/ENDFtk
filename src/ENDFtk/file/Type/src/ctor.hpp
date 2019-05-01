Type( std::vector< Section >&& sections ) :
  sectionMap( fill( std::move( sections ) ) ) {}

template< typename BufferIterator > 
Type( StructureDivision& division,
      BufferIterator& begin, const BufferIterator& end, long& lineNumber )
  try: sectionMap( read( division, begin, end, lineNumber ) ) {}
  catch ( std::exception& e ) {

    Log::info("Encountered error while generating file::Type<{}>", FileNumber );
    Log::info( "Line number: {}", lineNumber );
    throw e;  
  }

template < typename... Sections >
Type( Section&& section, Sections&&... sections ) :
  sectionMap( [] ( auto&&... sections ) {

    std::map< int, Section > map;
    auto insert_fn = insert{};
    int i[] = { (insert_fn( map, std::move( sections ) ), 0 )... };
    std::ignore = i;
    return map;
  }( std::move( section ), std::move( sections )... ) ) {}

