static void verify( int NPL ) {

  if ( NPL() != 18 ) {

    Log::error( "Encountered illegal NPL value" );
    Log::info( "NPL must be equal to 18" );
    Log::info( "NPL value: {}", ListRecord::NPL() );
    Log::info( "Line number: {}", lineNumber - ListRecord::NC() );
    throw std::exception();
  }
}
