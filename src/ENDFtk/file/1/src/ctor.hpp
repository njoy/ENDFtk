public:
template< int sectionNo, typename Args... >
Type( section::Type< 1, sectionNo >&& section_, Args&&... args ) :
  sectionMap( fill( std::move( section_ ),
		    std::forward< Args >( args )... ) ){}

template< typename BufferIterator >
Type( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber,
      int MAT )
try:
  sectionMap( read( structureDivision, begin, end, lineNumber, MAT ) ){
    if ( not structureDivision.isFend() ){
      if ( structureDivision.isHead() ){
        Log::error( "Inappropriate section encountered in file (MF) 1" );
        Log::info( "Section number (MT): {}", structureDivision.tail.MT );
        Log::info( "Line number: {}", lineNumber - 1 );
        throw std::runtime_error( "file::Type<1>::ctor" );
      } else if ( structureDivision.isMend() ){
        Log::error( "Encountered MEND record before"
		    " FEND record in file (MF) 1" );
        Log::info( "Line number: {}", lineNumber - 1 );
	throw std::runtime_error( "file::Type<1>::ctor" );
      } else if ( structureDivision.isTend() ){
        Log::error("Encountered TEND record before"
		   " FEND record in file (MF) 1" );
        Log::info("Line number: {}", lineNumber - 1 );
        throw std::runtime_error( "file::Type<1>::ctor" );
      }
    }
  } catch ( std::exception& e ){
    Log::info("Error while reading file (MF) 1");
    throw e;
  }
