template< typename Iterator >
Type ( HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try:
    Base( head, MAT, 1 ), lrp_( head.L1() ), lfi_( head.L2() ),
    nlib_( head.N1() ), nmod_( head.N2() ),
    parameters_( readParameters( begin, end, lineNumber, MAT ) ),
    description_( readRecords< TextRecord >( begin,
                                             end,
                                             lineNumber,
                                             MAT,
                                             this->parameters_[2].N1() ) ),
    index_( readRecords< DirectoryRecord >( begin,
                                            end,
                                            lineNumber,
                                            MAT,
                                            this->parameters_[2].N2() ) ) {
    readSEND(begin, end, lineNumber, MAT, 1 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section 451 of File 1 of Material {}",
               MAT );
    throw e;
  }

