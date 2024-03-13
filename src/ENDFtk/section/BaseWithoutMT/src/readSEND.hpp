template< typename Iterator >
static void readSEND
( Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF ) {

  try {

    const auto begin = it;
    auto division = StructureDivision( it, end, lineNumber );
    if ( not division.isSend() ) {

      Log::error( "Malformatted SEND record." );
      Log::info( "Error parsing line {}: \"{}\"",
                 lineNumber - 1,
                 std::string( begin, std::find( begin, end, '\n' ) ) );
      throw std::exception();
    }

    if ( MAT != division.tail.MAT() ) {

      Log::error( "Incorrect Material number (MAT) in SEND record." );
      Log::info( "Expected MAT = {}", MAT );
      Log::info( "Encountered MAT = {}", division.tail.MAT() );
      throw std::exception();
    }

    if ( MF != division.tail.MF() ) {

      Log::error( "Incorrect File number (MF) in SEND record" );
      Log::info( "Expected MF = {}", MF );
      Log::info( "Encountered MF = {}", division.tail.MF() );
      throw std::exception();
    }
  } catch ( std::exception& e ){
    Log::info( "Encountered error while reading the SEND record." );
    throw e;
  }
}
