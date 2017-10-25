template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  ControlRecord( this->ZA(), this->AWR(), this->LDG(),
                 this->LNU(), 0, 0 ).print( it, MAT, MF, MT() );
  std::visit( std::bind( [] ( const auto& v, OutputIterator& it,
                              int MAT, int MF, int MT ) -> void
                            { v.print( it, MAT, MF, MT ); },
                         std::placeholders::_1, it, MAT, MF, MT() ), this->lambda_ );
  std::visit( std::bind( [] ( const auto& v, OutputIterator& it,
                              int MAT, int MF, int MT ) -> void
                            { v.print( it, MAT, MF, MT ); },
                         std::placeholders::_1, it, MAT, MF, MT() ), this->nubar_ );
  SEND( MAT, MF ).print( it );
} 

