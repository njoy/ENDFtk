void generateComplexNumbers() {

  // generate the complex values
  std::vector< std::complex< double > > list;
  list.reserve( this->numberPoints() );
  for ( unsigned int i = 0; i < this->numberPoints(); ++i ) {

    list.emplace_back( this->real_.y()[i], this->imaginary_.y()[i] );
  }
  this->complex_ = list;
}
