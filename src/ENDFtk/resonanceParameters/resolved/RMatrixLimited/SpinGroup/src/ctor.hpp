SpinGroup( LIST&& channelDescriptions, LIST&& energyWidths ):
    channelDescriptions( std::move( channelDescriptions ) ),
    resonanceEnergyWidths( std::move( energyWidths ) ),
    KBK( channelDescriptions.L1() ),
    KPS( channelDescriptions.L2() )
{
  try {
  } catch ( std::exception& e ){
    Log::info( "Encountered errror while parsing RML SpinGrup" );
    throw e;
  }
}

template< typename Iterator >
SpinGroup( Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ) 
  try:
    SpinGroup( LIST( it, end, lineNumber, MAT, MF, MT ),
               LIST( it, end, lineNumber, MAT, MF, MT ) )
{
} catch ( std::exception& e ){
  Log::info( "Encountered errror while parsing RML SpinGrup" );
  throw e;
}

