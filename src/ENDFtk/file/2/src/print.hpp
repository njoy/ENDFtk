template< typename OutputIterator >
void print( OutputIterator& it, int MAT ) const {
  this->sectionMap[ 151_c ].print( it, MAT, MF() );
  hana::for_each( optionalSections, [&]( auto MT ){
                    const auto& section = this->sectionMap( MT );
                    if ( section ){ section->print( it, MAT, MF() ); } } );
  FEND( MAT ).print( it );
}
