const Section&
sectionNumber( int sectionNo ) const {
  try{
    return *( this->sectionMap.at( sectionNo ) );
  } catch( std::out_of_range& o ){
    Log::error( "Requested section number (MT) does not"
                " correspond to a stored section" );
    Log::info( "Requested section number: {}", sectionNo );
    Log::info( "File queried: ", FileNumber ); 
    throw o;
  }
}

Section& 
sectionNumber( int sectionNo ){
  return const_cast< Section& >(
      const_cast< const Type& >( *this ).sectionNumber( sectionNo ) );
}
