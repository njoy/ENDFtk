NBodyPhaseSpace( double APSX, long NPSX )
  try : ControlRecord( APSX, 0.0, 0, 0, 0, NPSX ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing n-body phase space "
               "distribution data (LAW=6)" );
    throw;
  }

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

