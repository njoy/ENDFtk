static void
verifyLF( int partialLF, int spectrumLF ) {

  // this function is called to verify the LF value between the spectrum and the
  // probability distribution when constructing a partial distribution in MF15

  if ( partialLF != spectrumLF ) {

    Log::error( "Inconsistent LF value between partial probability and "
                "spectrum" );
    Log::info( "LF must be equal to 1" );
    Log::info( "Partial probability LF value: {}", partialLF );
    Log::info( "Spectrum LF value: {}", spectrumLF );
    throw std::exception();
  }
}
