template< typename Iterator >
TabulationRecord readTable( Iterator& begin, 
                            const Iterator& end, 
                            long& lineNumber, 
                            int MAT, int MT ){

  TabulationRecord table( begin, end, lineNumber, MAT, 3, MT );

  const auto found = std::find_if( this->table.y().begin(),
                                   this->table.y().end(),
                                   []( auto y ) { return y < 0.0; } );
  if( found != this->table.y().end() ){
    Log::error( "Encountered negative cross section value" );
    Log::info( "See section {} of file 3 of material {}", MT, MAT );
    Log::info( "TAB1 entry [{}]: {}",
               std::distance( this->table.y().begin(), found ), *found );
    throw std::exception();
  }

  return table;
}
