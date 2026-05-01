template<typename Iterator>
static void readFendOrSend
( Iterator&it, const Iterator& end, long& lineNumber, int MAT, int MF ) {

  try {

    const auto begin = it;
    auto division = StructureDivision(it, end, lineNumber);
    if ( ( ! division.isFend() ) && ( ! division.isSend() ) ) {

        Log::error( "Malformatted FEND or SEND record.");
        Log::info( "Error parsing line {}: \"{}\"",
                   lineNumber - 1,
                   std::string( begin, std::find( begin, end, '\n' ) ) );
        throw std::exception();
    }

    if ( MAT != division.tail.MAT() ) {

        Log::error("Incorrect Material number (MAT) in FEND record.");
        Log::info("Expected MAT = {}", MAT);
        Log::info("Encountered MAT = {}", division.tail.MAT());
        throw std::exception();
    }

    if ( division.isSend() && MF != division.tail.MF() ) {

      Log::error( "Incorrect File number (MF) in SEND record" );
      Log::info( "Expected MF = {}", MF );
      Log::info( "Encountered MF = {}", division.tail.MF() );
      throw std::exception();
    }
  }
  catch (std::exception& e) {

    Log::info( "Encountered error while reading the FEND record." );
    throw e;
  }
}