template< typename Iterator >
static std::vector< DiscretePhoton >
readDiscretePhotons( Iterator& begin,
                     const Iterator& end,
                     long& lineNumber,
                     int MAT,
                     int NG ) {
    std::vector< DiscretePhoton > records;
    if ( NG < 1 ) {
      Log::error( "Encountered illegal NG value for LO=1" );
      Log::info( "NG must be greater than 0" );
      Log::info( "NG value: {}", NG );
      Log::info( "Line number: {}", lineNumber - 1 );
      throw std::exception();
    }
    records.reserve( NG );

    while( NG-- ){
      records.emplace_back( begin, end, lineNumber, MAT, 1, 460 );
    }

    return records;
}

