std::vector< double > energies() const {
  if( table ){
    return this->table->x() | ranges::to_vector;
  }
  else{
    return std::vector< double >();
  }
}
