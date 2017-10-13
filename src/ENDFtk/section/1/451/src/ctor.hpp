template< typename Iterator >
Type ( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
  try: Base( head, MAT, 1 ), lrp_( head.L1() ), lfi_( head.L2() ),
       nlib_( head.N1() ), nmod_( head.N2() ),
       parameters_{ ControlRecord( begin, end, lineNumber, MAT, 1, 451 ),
                    ControlRecord( begin, end, lineNumber, MAT, 1, 451 ),
                    ControlRecord( begin, end, lineNumber, MAT, 1, 451 ) },
       description_( readRecords< TextRecord >( begin, end, lineNumber, MAT,
                                  parameters_[2].N1(), 0 ,
                                  "Number of descriptive records (NWD) must be greater than or equal to zero" ) ),
       index_( readRecords< DirectoryRecord >( begin, end, lineNumber, MAT,
                            parameters_[2].N2(), 1 ,
                            "Number of index records (NXC) must be greater than or equal to one" ) ) {
    readSEND(begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 1 of Material {}", 451, MAT );
    throw e;
  }

