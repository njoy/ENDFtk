template< typename Iterator >
static auto
readParameters( Iterator& it, const Iterator& end, long& lineNumber, int MAT ){
  auto line0 = ControlRecord( it, end, lineNumber, MAT, 1, 451 );
  auto line1 = ControlRecord( it, end, lineNumber, MAT, 1, 451 );
  auto line2 = ControlRecord( it, end, lineNumber, MAT, 1, 451 );
  if ( line2.N1() < 0 ){
    Log::error( "Encountered illegal NWD value" );
    Log::info( "NWD must be greater than or equal to zero" );
    Log::info( "NWD value: {}", line2.N1() );
    Log::info( "Line number: {}", lineNumber - 1 );
    throw std::exception();
  }
  if ( line2.N2() < 1 ){
    Log::error( "Encountered illegal NXC value" );
    Log::info( "NXC must be greater than or equal to one" );
    Log::info( "NXC value: {}", line2.N2() );
    Log::info( "Line number: {}", lineNumber - 1 );
    throw std::exception();
  }
  return std::array< ControlRecord, 3 >{{ line0, line1, line2 }};
}
