/*
public:
template< typename Args... >
Type( section::Type< 1, 451 >&& section_, Args&&... args ) :
  Type( fill( std::move( section_ ), std::forward< Args >( args )... ) ){}

protected:
Type( StructureDivision& structureDivision,
      long& lineNumber,
      section::Type< 1, 451 >&& section451,
      std::optional< section::Type< 1, 452 > >&& section452,
      std::optional< section::Type< 1, 452 > >&& section455,
      std::optional< section::Type< 1, 456 > >&& section456,
      std::optional< section::Type< 1, 458 > >&& section458,
      std::optional< section::Type< 1, 460 > >&& section460 ) :
  sectionMap( hana::make_map
              ( hana::make_pair( 451_c, std::move(section451) ),
                hana::make_pair( 452_c, std::move(section452) ),
                hana::make_pair( 455_c, std::move(section455) ),
                hana::make_pair( 456_c, std::move(section456) ),
                hana::make_pair( 458_c, std::move(section458) ),
                hana::make_pair( 460_c, std::move(section460) ) ) ){
  if ( not structureDivision.isFend() ){
    if ( structureDivision.isHead() ){
      Log::error("Inappropriate section encountered in File 1");
      Log::info("Section number: {}", asHead( structureDivision ).section() );
      Log::info("Line number: {}", lineNumber - 1 );
      throw std::exception{};
    } else if ( structureDivision.isMend() ){
      Log::info("Encountered MEND record before FEND record in File 1" );
      Log::info("Line number: {}", lineNumber - 1 );
      throw std::exception{};
    } else if ( structureDivision.isTend() ){
      Log::info("Encountered TEND record before FEND record in File 1" );
      Log::info("Line number: {}", lineNumber - 1 );
      throw std::exception{};
    }
  }
}

template< typename BufferIterator >
Type( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber,
      int MAT,
      section::Type< 1, 451 >&& section451,
      std::optional< section::Type< 1, 452 > >&& section452,
      std::optional< section::Type< 1, 452 > >&& section455,
      std::optional< section::Type< 1, 456 > >&& section456,
      std::optional< section::Type< 1, 458 > >&& section458 ) :
  Type( structureDivision, lineNumber,
        std::move(section451),
        std::move(section452),
        std::move(section455),
        std::move(section456),
        std::move(section458),
        read( 460_c, structureDivision, begin, end, lineNumber, MAT ) ){}

template< typename BufferIterator >
Type( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber,
      int MAT,
      section::Type< 1, 451 >&& section451,
      std::optional< section::Type< 1, 452 > >&& section452,
      std::optional< section::Type< 1, 452 > >&& section455,
      std::optional< section::Type< 1, 456 > >&& section456 ) :
  Type( structureDivision, begin, end, lineNumber, MAT,
        std::move(section451),
        std::move(section452),
        std::move(section455),
        std::move(section456),
        read( 458_c, structureDivision, begin, end, lineNumber, MAT ) ){}

template< typename BufferIterator >
Type( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber,
      int MAT,
      section::Type< 1, 451 >&& section451,
      std::optional< section::Type< 1, 452 > >&& section452,
      std::optional< section::Type< 1, 455 > >&& section455 ) :
  Type( structureDivision, begin, end, lineNumber, MAT,
        std::move(section451),
        std::move(section452),
        std::move(section455),
        read( 456_c, structureDivision, begin, end, lineNumber, MAT ) ){}

template< typename BufferIterator >
Type( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber,
      int MAT,
      section::Type< 1, 451 >&& section451,
      std::optional< section::Type< 1, 452 > >&& section452 ) :
  Type( structureDivision, begin, end, lineNumber,
        std::move(section451),
        std::move(section452),
        read( 455_c, structureDivision, begin, end, lineNumber, MAT ) ){}

template< typename BufferIterator >
Type( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber,
      int MAT,
      section::Type< 1, 451 >&& section451 ) :
  Type( structureDivision, begin, end, lineNumber, MAT,
        std::move(section451),
        read( 452_c, structureDivision, begin, end, lineNumber, MAT ) ){}

public:
template< typename BufferIterator >
Type( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber,
      int MAT )
try:
  Type( structureDivision, begin, end, lineNumber, MAT,
        read( 451_c, structureDivision, begin, end, lineNumber, MAT ) ){
} catch ( std::exception& e ){
  Log::info("Error while reading File 1");
  throw e;
}
*/

// stopgap until remainder of file 1 complete
public:
Type( section::Type< 1, 451 >&& section451 ) :
  sectionMap( hana::make_map
              ( hana::make_pair( 451_c, std::move(section451) ) ) ){}

template< typename BufferIterator >
Type( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber )
try:
  Type( this->read( 451_c, structureDivision, begin, end, lineNumber ) ){
    if ( not structureDivision.isFend() ){
      if ( structureDivision.isHead() ){
        Log::error("Inappropriate section encountered in File 1");
        Log::info("Section number: {}", asHead( structureDivision ).section() );
        Log::info("Line number: {}", lineNumber - 1 );
        throw std::exception{};
      } else if ( structureDivision.isMend() ){
        Log::info("Encountered MEND record before FEND record in File 1" );
        Log::info("Line number: {}", lineNumber - 1 );
        throw std::exception{};
      } else if ( structureDivision.isTend() ){
        Log::info("Encountered TEND record before FEND record in File 1" );
        Log::info("Line number: {}", lineNumber - 1 );
        throw std::exception{};
      }
    }
} catch ( std::exception& e ){
  Log::info("Error while reading File 1");
  throw e;
}
