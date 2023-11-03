static void
verifyMEND( const StructureDivision& structureDivision,
           long lineNumber ) {

  if ( not structureDivision.isMend() ) {

    Log::error( "Expected MEND record" );
    Log::info("Line number: {}", lineNumber );
    throw std::exception{};
  }
}
