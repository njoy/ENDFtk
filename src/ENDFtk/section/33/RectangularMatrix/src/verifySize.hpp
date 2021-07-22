/*
 * @brief Verify that sizes are consistent/possible.
 *
 * NEC can be derived from NER, but this requires an appropriate selection
 * of values.  NEC = (NT-1)/NER.  The remainder in this division must be 0.
 */
static void
verifySize( int NT, int NER ) {

  // check remainder
  if ( (NT-1) % NER != 0 ) {

    Log::error( "Inconsistent number of values in rectangular matrix" );
    Log::info( "NT: {}", NT );
    Log::info( "NER: {}", NER );
    Log::info( "NEC Remainder: {}", (NT-1) % NER );
    throw std::exception();
  }

}

static void
verifySize( int NT, int NER, int size ) {

  verifySize( NT, NER );

  // check total number of energies
  int NEC = (NT-1) / NER;
  if ( NEC + NER != size ) {

    Log::error( "Inconsistent number of energies in rectangular matrix" );
    Log::info( "NEC: {}", NEC );
    Log::info( "NER: {}", NER );
    Log::info( "Energy size: {}", size );
    throw std::exception();
  }

}
