template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  ControlRecord( this->ZA(), this->AWR(), 0,
                 this->LFC(), 0, this->NFC() ).print( it, MAT, MF, MT() );
  std::visit( std::bind( [] ( const auto& v, OutputIterator& it,
                              int MAT, int MF, int MT ) -> void
                            { v.print( it, MAT, MF, MT ); },
                         std::placeholders::_1, it, MAT, MF, MT() ), this->data_ );
  SEND( MAT, MF ).print( it );
} 

