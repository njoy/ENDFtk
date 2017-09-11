static void
verifyN2( long n2, long index ) {
  if ( n2 != index ) {
    InconsistentN2 exception( n2, index);
    throw exception;
  }
}
