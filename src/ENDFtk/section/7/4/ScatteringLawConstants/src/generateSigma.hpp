void generateSigma() {

  this->sigma_.clear();
  this->sigma_.push_back( ListRecord::list()[0] );

  auto ns = this->NS();
  for ( unsigned int i = 0; i < ns; ++i ) {

    this->sigma_.push_back( ListRecord::list()[ 7 + i * 6 ] );
  }
}
