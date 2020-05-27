const Section_t& section( int MF, int MT ) const {
  try{
    return this->files_.at( MFMT(MF, MT) );
  } catch( std::out_of_range& o ){
    Log::error
      ( "Requested MF/MT does not "
        "correspond to a stored section in the syntax tree" );
    Log::info( "Requested MF/MT: {}/{}", MF, MT );
    Log::info( "Material number of queried material syntax tree: {}",
               this->materialNumber() );
    throw o;
  }   
}
