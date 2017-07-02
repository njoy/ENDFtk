Section_t&
sectionNumber( int sectionNo ){
  try{
    return this->sectionMap.at( sectionNo );
  } catch( std::out_of_range& o ){
    Log::error( "Requested section number (MT) does not"
                " correspond to a stored section in the syntax tree" );
    Log::info( "Requested section number: {}", sectionNo );
    Log::info( "File number of queried file syntax tree: {}",
	       this->fileNumber() );
    throw o;
  }   
}
