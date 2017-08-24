template< typename Iterator >
Type ( HEAD& head, 
       Iterator& begin, 
       const Iterator& end, 
       long& lineNumber, 
       int MAT )
  try: Base( head, MAT, 3 ),
       table( begin, end, lineNumber, head.MAT(), 3, head.MT() ){ 
    const auto found = std::find_if( this->table.y().begin(),
                                     this->table.y().end(),
                                     []( auto y ) { return y < 0.0; } );
    if( found != this->table.y().end() ){
      Log::error( "Encountered negative cross section value" );
      Log::info( "See section {} of file 3 of material {}", head.MT(), MAT );
      Log::info( "TAB1 entry [{}]: {}",
                 std::distance( this->table.y().begin(), found ), *found );
      throw std::exception();
    }
    readSEND(begin, end, lineNumber, MAT, 3 );
  } catch( std::exception& e ){
    Log::info
    ( "Encountered error while reading section {} of file 3 of material {}",
      head.MT(), MAT );
    throw e;
  }
