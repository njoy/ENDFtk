template< typename Iterator >
static Base
readMetadata
( Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF, int MT ){
  try{
    Base metadata( it, end );
    verifyTail( it, end, lineNumber, MAT, MF, MT );
    if ( std::get<4>( metadata.fields ) < 0 ){
      Log::error( "Illegal NPL value encountered" );
      Log::info( "NPL must be greater than or equal to 0" );
      Log::info( "NPL value: ", std::get<4>( metadata.fields ) );
      throw std::runtime_error( "List Record NPL value" );
    }
    return metadata;
  } catch ( std::exception& e ){
    Log::info( "Error while reading metadata" );
    throw e;
  }
}
