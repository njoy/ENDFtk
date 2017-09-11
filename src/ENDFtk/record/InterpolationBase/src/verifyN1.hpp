static void
verifyN1( long n1, unsigned int size ) {
  if ( n1 != size ) {
    Log::error( "Inconsistent value for NR" );
    Log::info( "Expected {} interpolation ranges but found {}", n1, size );
    throw std::exception();
  }
}
