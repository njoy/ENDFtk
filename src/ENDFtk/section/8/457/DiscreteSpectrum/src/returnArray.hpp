std::array< double, 2 >
returnArray( int index ) const {
  if ( this->NT() > index ) {
    return {{ ListRecord::list()[index], ListRecord::list()[index+1] }};
  }
  else {
    return {{ 0.0, 0.0 }};
  }
}  
