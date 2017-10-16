std::vector< double > crossSections() const {
  if( table ){
    return this->table->y() | ranges::to_vector;
  }
  else{
    return std::vector< double >();
  }
}
