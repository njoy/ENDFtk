static void
verifyLF( int partialLF, int spectrumLF ) {

  if ( partialLF != spectrumLF ) {

    Log::error( "Inconsistent LF value between partial probability and "
                "spectrum" );
    Log::info( "LF must be equal to 1" );
    Log::info( "Partial probability LF value: {}", partialLF );
    Log::info( "Spectrum LF value: {}", spectrumLF );
    throw std::exception();
  }
}
