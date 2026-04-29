template < typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {

  int MT = this->MT();
  ControlRecord( this->ZA(), this->AWR(), this->NL(), this->NZ(),
                 this->LRFLAG(), this->NGN() ).print( it, MAT, MF, MT );
  auto records = makeRecords( this->temp_, this->flux_, this->matrix_ );
  for ( const auto& record : records) { record.print( it, MAT, MF, MT ); }
  SEND( MAT, MF ).print( it );
}