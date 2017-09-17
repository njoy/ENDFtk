template< typename Iterator >
auto
readAPE( const Base& base,
         Iterator& it, const Iterator& end, long& lineNumber,
         int MAT, int MF, int MT ){
  return ( base.NRO() ) ?
    std::optional< TAB1 >{ TAB1( it, end, lineNumber, MAT, MF, MT ) } :
    std::nullopt;
}
