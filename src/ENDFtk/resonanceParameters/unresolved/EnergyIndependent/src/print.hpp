template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  using Format = disco::Record< disco::ENDF, disco::ENDF,
                                disco::Integer< 11 >, disco::Integer< 11 >,
                                disco::Integer< 11 >, disco::Integer< 11 >,
                                disco::Integer< 4 >, disco::Integer< 2 >,
                                disco::Integer< 3 >, disco::ColumnPosition< 5 > >;

  Format::write( it,
                 this->EL(), this->EH(),
                 this->LRU(), this->LRF(),
                 this->NRO(), this->NAPS(), MAT, MF, MT );
  
  if ( this->ape ){ this->ape->print( it, MAT, MF, MT ); }

  Format::write( it,
                 this->SPI(),
                 this->AP(),
                 this->LSSF(),
                 0,
                 this->NLS(),
                 0, MAT, MF, MT );

  for( const auto& list : this->lists ){ list.print( it, MAT, MF, MT ); }
}

