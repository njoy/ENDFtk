template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {

  int MT = this->MT();
  if ( this->covariances_.begin()->second.empty() ) {

      ControlRecord( this->ZA(), this->AWR(), 0, this->MTL(),
                     this->LRFLAG(), 0 ).print( it, MAT, MF, MT );
  } // endif
  else {

      ControlRecord( this->ZA(), this->AWR(), 0, 0, this->LRFLAG(),
                  this->NSMT() ).print( it, MAT, MF, MT );
      auto records = makeRecords( this->covariances_ );
      for ( const auto& record : records )       {

          record.print( it, MAT, MF, MT );
      }
  }
  SEND( MAT, MF ).print( it );
}
