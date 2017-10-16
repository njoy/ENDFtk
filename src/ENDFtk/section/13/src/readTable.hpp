template< typename Iterator >
std::optional< TabulationRecord > readTable( Iterator& begin, 
                                             const Iterator& end, 
                                             long& lineNumber, 
                                             int MAT, int MT, int NK ){

  if( NK > 1 ){
    return TabulationRecord( begin, end, lineNumber, MAT, 13, MT );
  }
  else{
    return std::nullopt;
  }
}
