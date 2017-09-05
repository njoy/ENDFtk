template< typename Iterator >
static Base
readMetadata( Iterator& it, const Iterator& end, long& lineNumber,
              int MAT, int MF, int MT ){
  try{
    Base metadata( it, end );
    verifyTail( it, end, lineNumber, MAT, MF, MT );
    if ( std::get<4>( metadata.fields ) < 0 ){
      Log::error( "Illegal NR value encountered" );
      Log::info( "NR (or number of regions) must be greater than or equal to 0" );
      Log::info( "NR value: {}", std::get<4>( metadata.fields ) );
      throw std::runtime_error( "NR value" );
    }
    if ( std::get<5>( metadata.fields ) < 0 ){
      Log::error( "Illegal NZ or NP value encountered" );
      Log::info( "NZ or NP must be greater than or equal to 0" );
      Log::info( "NZ or NP value: {}", std::get<5>( metadata.fields ) );
      throw std::runtime_error( "NZ or NP value" );
    }
    return metadata;
  } catch (std::exception& e){
    Log::info( "Error while reading metadata" );
    throw e;
  }
}
