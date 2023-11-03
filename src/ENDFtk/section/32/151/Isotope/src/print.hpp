template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {

  ControlRecord( this->ZAI(), this->ABN(),
                 0, this->LFW(),
                 this->NER(), 0 ).print( it, MAT, MF, MT );
  for ( const auto& entry : this->ranges_ ) { entry.print( it, MAT, MF, MT ); }
}
