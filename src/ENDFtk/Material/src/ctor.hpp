protected:
Material( int MAT, Map&& map ) : mat_( MAT ), fileMap( std::move(map) ){}

public:
template< int fileNo, typename... Args >
Material( file::Type< fileNo >&& file_, Args&&... args ) :
  Material( fill( std::move( file_ ), std::forward< Args >( args )... ) ) {}

protected:
template< typename BufferIterator >
Material( int MAT,
          StructureDivision& structureDivision,
          BufferIterator& begin,
          const BufferIterator& end,
          long& lineNumber ) :
  Material( MAT, this->read( files(),
                             structureDivision, begin, end, lineNumber ) ) {}

public:
template< typename BufferIterator >
Material( StructureDivision& structureDivision,
          BufferIterator& begin,
          const BufferIterator& end,
          long& lineNumber )
  try: Material( structureDivision.tail.MAT(),
                 structureDivision, begin, end, lineNumber ) {

    this->verifyEND( structureDivision, lineNumber );
  }
  catch ( std::exception& e ) {

    Log::info( "Error while reading material {}",
               structureDivision.tail.MAT() );
    throw e;
  }
