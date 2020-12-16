template< typename Iterator >
static auto
readParameters( Iterator& it, const Iterator& end, long& lineNumber, int MAT ) {

  auto line0 = ControlRecord( it, end, lineNumber, MAT, 1, 451 );
  auto line1 = ControlRecord( it, end, lineNumber, MAT, 1, 451 );
  auto line2 = ControlRecord( it, end, lineNumber, MAT, 1, 451 );
  if ( line2.N1() < 0 ){
    Log::error( "Number of descriptive records (NWD) must be greater than or equal to zero" );
    Log::info( "See line {}", lineNumber - 1 );
    throw std::runtime_error("Number of descriptive records (NWD) must be greater than or equal to zero");
  }
  if ( line2.N2() < 1 ){
    Log::error( "Number of index records (NXC) must be greater than or equal to one" );
    Log::info( "See line {}", lineNumber - 1 );
    throw std::runtime_error("Number of index records (NXC) must be greater than or equal to one");
  }
  return std::array< ControlRecord, 3 >{{ line0, line1, line2 }};
}
