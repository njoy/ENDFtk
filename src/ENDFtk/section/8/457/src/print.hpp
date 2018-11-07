template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
  int MT = this->MT();
  ControlRecord( this->ZA(), this->AWR(), this->lis_, this->liso_,
                 this->nst_, 0 ).print( it, MAT, MF, MT );
  this->energies_.print( it, MAT, MF, MT );
  this->modes_.print( it, MAT, MF, MT );
  for ( const auto& entry : this->spectra_ ) { entry.print( it, MAT, MF, MT ); }
  SEND( MAT, MF ).print( it );
} 
