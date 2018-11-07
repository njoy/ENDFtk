std::tuple< double, double >
returnTuple( int index ) const {
  if ( this->NT() > index ) {
    return std::tuple< double, double >( ListRecord::list()[index],
                                         ListRecord::list()[index+1] );
  }
  else {
    return std::tuple< double, double >( 0.0, 0.0 );
  }
}  
