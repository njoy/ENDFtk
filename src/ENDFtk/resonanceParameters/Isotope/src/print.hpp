template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {

  ControlRecord( this->ZAI(), this->ABN(),
                 0, this->LFW(),
                 this->ranges.size(), 0 ).print( it, MAT, MF, MT );
  for ( const auto& entry : this->ranges ) {

    std::visit( [&] ( const auto& v ) -> void
                    { v.print( it, MAT, MF, MT ); },
                entry );
  }
} 

