template <typename OutputIterator>
void print( OutputIterator& it, int MAT, int MF ) const {

  int MT=451;
  ControlRecord( this->ZA(), this->AWR(), 0, this->NZ(),
                 this->NGT(), this->NWT() ).print(it, MAT, MF, MT );
  parameters_.print(it, MAT, MF, MT);
  FEND(MAT).print(it);
}