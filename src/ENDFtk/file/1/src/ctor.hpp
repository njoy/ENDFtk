protected:
Type( Map&& map ) : sectionMap( std::move(map) ){}

public:
template< int sectionNo, typename... Args >
Type( section::Type< 1, sectionNo >&& section_, Args&&... args ) :
  Type( fill( std::move( section_ ), std::forward< Args >( args )... ) ) {}

template< typename BufferIterator >
Type( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber )
  try: Type( this->read( sections(),
                       structureDivision, begin, end, lineNumber,
                       structureDivision.tail.MAT() ) ) {

    this->verifyEND( structureDivision, lineNumber );
  }
  catch ( std::exception& e ) {

    Log::info("Error while reading File 1");
    throw e;
  }
