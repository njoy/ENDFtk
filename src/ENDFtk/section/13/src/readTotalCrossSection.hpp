template< typename Iterator >
static std::optional< TotalCrossSection >
readTotalCrossSection( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT,
                       int size ) {

  if ( size == 1 ) {

    return std::nullopt;
  }

  return std::make_optional( TotalCrossSection( begin, end, lineNumber,
                                                MAT, MF, MT ) );
}
