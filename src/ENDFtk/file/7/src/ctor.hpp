protected:
Type( Map&& map ) : sectionMap( std::move(map) ){}

public:
template< int sectionNo, typename... Args >
Type( section::Type< 7, sectionNo >&& section_, Args&&... args ) :
  Type( fill( std::move( section_ ), std::forward< Args >( args )... ) ) {}

template< typename BufferIterator >
Type( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber )
try:
  Type( this->read( sections(),
                    structureDivision, begin, end, lineNumber,
                    structureDivision.tail.MAT() ) ) {
    if ( not structureDivision.isFend() ){
      if ( structureDivision.isSend() ){
        Log::error("Encountered duplicate SEND record in File 7");
        Log::info("Line number: {}", lineNumber );
        throw std::exception{};
      } else if ( structureDivision.isHead() ){
        Log::error("Inappropriate section encountered in File 7");
        Log::info("Section number: {}", asHead( structureDivision ).section() );
        Log::info("Line number: {}", lineNumber );
        throw std::exception{};
      } else if ( structureDivision.isMend() ){
        Log::info("Encountered MEND record before FEND record in File 7" );
        Log::info("Line number: {}", lineNumber );
        throw std::exception{};
      } else if ( structureDivision.isTend() ){
        Log::info("Encountered TEND record before FEND record in File 7" );
        Log::info("Line number: {}", lineNumber );
        throw std::exception{};
      }
    }
  } catch ( std::exception& e ){
    Log::info("Error while reading File 7");
    throw e;
}
