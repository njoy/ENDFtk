const File_t&
file( int fileNo ) const {
  try{
    return this->files_.at( fileNo );
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

File_t&
file( int fileNo ) {
  return const_cast< File_t& >
         ( const_cast< const Material& >( *this ).file( fileNo ) );
}
