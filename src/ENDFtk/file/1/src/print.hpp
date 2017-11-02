template< typename OutputIterator >
void print( OutputIterator& it, int MAT ) const {
  hana::for_each( sections, [&]( auto pair ){
      const auto MT = hana::second( pair );
      const auto& section = this->sectionMap( MT );
      if ( section ){ section->print( it, MAT, MF() ); } } );
  FEND( MAT ).print( it );
}

