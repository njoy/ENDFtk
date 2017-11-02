template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  ControlRecord( this->ZA(), this->AWR(), this->LDG(),
                 this->LNU(), 0, 0 ).print( it, MAT, MF, MT() );
  std::visit( [&] ( const auto& v ) -> void
                  { v.print( it, MAT, MF, MT() ); },
              this->lambda_ );
  std::visit( [&] ( const auto& v ) -> void
                  { v.print( it, MAT, MF, MT() ); },
              this->nubar_ );
  SEND( MAT, MF ).print( it );
} 

