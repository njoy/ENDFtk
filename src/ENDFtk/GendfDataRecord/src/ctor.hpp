template< typename Iterator >
GendfDataRecord( Iterator& it,
                 const Iterator& end,
                 long& lineNumber,
                 int MAT,
                 int MF,
                 int MT )
  : ListRecord( it, end, lineNumber, MAT, MF, MT ) {}
