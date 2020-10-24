static void
verifyLTP( int LTP ) {

  if ( ( LTP != 12 ) and ( LTP != 14 ) and ( LTP != 15 ) ) {

    Log::error( "Encountered illegal LTP value" );
    Log::info( "LTP must be equal to 12, 14 or 15 for nuclear "
               "plus interference");
    Log::info( "LTP value: {}", LTP );
    throw std::exception();
  }
}
