template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  ControlRecord( this->ZA(), this->AWR(), 0,
                 this->LNU(), 0, 0 ).print( it, MAT, MF, this->MT() );
  std::visit( [&] ( const auto& v ) -> void
                  { v.print( it, MAT, MF, this->MT() ); },
              this->nubar() );
  SEND( MAT, MF ).print( it );
}
