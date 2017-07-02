File_t&
fileNumber( int fileNo ){
  try{
    return this->fileMap.at( fileNo );
  } catch( std::out_of_range& o ){
    Log::error
      ( "Requested file number (MF) does not"
  " correspond to a stored file syntax tree" );
    Log::info( "Requested file number: {}", fileNo );
    Log::info( "Material number of queried material syntax tree: ",
         this->materialNumber() );
    throw o;
  }   
}
