void checkRedundant( bool test ) {
  if ( test ) {
    Log::error( "Sections specified with redundant section numbers (MT)" );
    Log::info( "Within an ENDF File, sections are required to specify a unique MT" );
    Log::info( "Encountered redundant MT: {}", division.tail.MT() );
    throw std::exception();
  }
}
