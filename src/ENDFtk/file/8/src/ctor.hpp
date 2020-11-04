protected:
Type( Map&& map ) : sectionMap( std::move(map) ){}

public:
template< int sectionNo, typename... Args >
Type( section::Type< 8, sectionNo >&& section_, Args&&... args ) :
  Type( fill( std::move( section_ ), std::forward< Args >( args )... ) ) {}

template< typename BufferIterator >
Type( StructureDivision& division,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber ) {

    try {

      if ( ( division.tail.MT() == 454 ) ||
           ( division.tail.MT() == 457 ) ||
           ( division.tail.MT() == 459 ) ) {

        this->sectionMap = this->read( sections(),
                                       division, begin, end, lineNumber,
                                       division.tail.MAT() );
      }
      else {

        int MF = 8;
        if ( division.tail.MF() == MF ) {

          Log::info( "Found unsupported file MF{} - skipping file", MF );

          while ( division.tail.MF() == MF ) {

            Tail tail( division.tail.MAT(), division.tail.MF(), division.tail.MT() );
            int MT = tail.MT();
            while ( tail.MT() == MT ) {

              Text( begin, end );
              tail = Tail( begin, end, lineNumber );
            }
            division = StructureDivision( begin, end, lineNumber );
          }
        }
      }

      this->verifyEND( division, lineNumber );
    }
    catch ( std::exception& e ) {

      Log::info("Error while reading File 8");
      throw e;
    }
  }
