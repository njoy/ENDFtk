template< typename Iterator >
DataType ( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
  try: Base( head, MAT, 1 ), lrp_( head.L1() ), lfi_( head.L2() ),
       nlib_( head.N1() ), nmod_( head.N2() ),
       parameters_( readRecords( begin, end, lineNumber, MAT, 3, 3, "" ) ),
       description_( readRecords( begin, end, lineNumber, MAT,
                                  parameters_[3].N1(), 0 ,
                                  "Number of descriptive records (NWD) must be greater than or equal to zero" ) ),
       index_( readRecords( begin, end, lineNumber, MAT,
                            parameters_[3].N2(), 1 ,
                            "Number of index records (NXC) must be greater than or equal to one" ) ) {
    readSEND(begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 1 of Material {}", 451, MAT );
    throw e;
  }

