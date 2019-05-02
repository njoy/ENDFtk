NBodyPhaseSpace( double APSX, long NPSX ) :
  // this can never fail, try-catch would be unreachable
  ControlRecord( APSX, 0.0, 0, 0, 0, NPSX ) {}

template< typename Iterator >
NBodyPhaseSpace( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT )
  try : ControlRecord( begin, end, lineNumber, MAT, MF, MT  ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading n-body phase space "
               "distribution data (LAW=6)" );
    throw;
  }

