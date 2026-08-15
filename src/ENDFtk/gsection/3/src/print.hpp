template <typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {

  int MT = this->MT();
  if ( this->isErrorr() ) {

    ListRecord( this->ZA(), this->AWR(), 0, 0, 0,
                std::vector< double >( this->sigma_[0][0] ) ).print( it, MAT, MF, MT );
  }
  else {

    ControlRecord( this->ZA(), this->AWR(), this->NL(), this->NZ(),
                   this->LR(), this->NGN() ).print( it, MAT, MF, MT ) ;
    auto records = makeRecords( this->temp_, this->flux_, this->sigma_, this->ratio_ );
    for ( const auto& record : records ) { record.print(it, MAT, MF, MT ); }
  }
  SEND( MAT, MF ).print( it );
}