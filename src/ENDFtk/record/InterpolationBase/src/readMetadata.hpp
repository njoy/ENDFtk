template< typename Iterator >
static Base
readMetadata( Iterator& it, const Iterator& end, long& lineNumber,
              int MAT, int MF, int MT ){
  Base metadata( it, end );
  verifyTail( it, end, lineNumber, MAT, MF, MT );
  if ( std::get<4>( metadata.fields ) < 1 ){
    Log::error( "Illegal NR value encountered" );
    Log::info( "NR (or number of regions) must be greater than or equal to 1" );
    Log::info( "NR value: {}", std::get<4>( metadata.fields ) );
    throw std::exception();
  }
  if ( std::get<5>( metadata.fields ) < 0 ){
    IllegalN2 exception( std::get<5>( metadata.fields ) );
    throw exception;
  }
  return metadata;
}
