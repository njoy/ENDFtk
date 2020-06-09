template< typename Iterator >
GendfDataRecord( Iterator& it,
                 const Iterator& end,
                 long& lineNumber,
                 int num_legendre,
                 int num_sigma0,
                 int MAT,
                 int MF,
                 int MT )
  : ListRecord( it, end, lineNumber, MAT, MF, MT ),
    num_legendre_( num_legendre ),
    num_sigma0_( num_sigma0 ) {}
