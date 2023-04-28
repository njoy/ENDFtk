static void
verifyFEND( const StructureDivision& structureDivision,
            long lineNumber ) {

  if ( not structureDivision.isFend() ) {

    int MF = Base::MF();
    if ( structureDivision.isSend() ) {

      Log::error( "Encountered duplicate SEND record in File {}", MF );
      Log::info("Line number: {}", lineNumber );
      throw std::exception{};
    }
    else if ( structureDivision.isHead() ) {

      Log::error( "Inappropriate section encountered in File {}", MF );
      Log::info( "Section number: {}", asHead( structureDivision ).section() );
      Log::info( "Line number: {}", lineNumber );
      throw std::exception{};
    }
    else if ( structureDivision.isMend() ) {

      Log::error( "Encountered MEND record before FEND record in File {}", MF );
      Log::info( "Line number: {}", lineNumber );
      throw std::exception{};
    }
    else if ( structureDivision.isTend() ) {

      Log::error( "Encountered TEND record before FEND record in File {}", MF );
      Log::info( "Line number: {}", lineNumber );
      throw std::exception{};
    }
  }
}
