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

Type( const Type& other ) :
  sectionMap( other.sectionMap ) {}

Type( Type&& other ) noexcept = default;
