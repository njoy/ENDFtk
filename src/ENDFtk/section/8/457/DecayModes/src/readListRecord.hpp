template< typename Iterator >
static ListRecord
readListRecord( Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT ) {

  ListRecord list( it, end, lineNumber, MAT, MF, MT );
  if ( list.NPL() == 0 && list.N2() == 0 ) {

    Log::warning( "Encountered inconsistent NPL and NDK values" );
    Log::info( "NPL should be equal to 6 if NDK=0, data has been updated accordingly" );
    Log::info( "NPL value: {}", list.NPL() );
    Log::info( "NDK value: {}", list.N2() );

    // replace the list record read with what the ENDF file says it should be
    list = ListRecord( list.C1(), list.C2(), 0, 0, 0,
                       { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } );
  }
  return list;
}
