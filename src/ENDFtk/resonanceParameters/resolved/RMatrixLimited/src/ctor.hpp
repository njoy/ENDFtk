template< typename Iterator >
RMatrixLimited( Base&& base, 
                Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT ) :
  Base( std::move( base ) ){

  try {
    CONT cont(it, end, lineNumber, MAT, MF, MT);
    IFG = cont.L1();
    KRM = cont.L2();
    KRL = cont.N2();

    gammaPlusCompoundNucleus = LIST( it, end, lineNumber, MAT, MF, MT);

    int NRJ = cont.N1();
    for( int nrj = 0; nrj < NRJ; ++nrj ){
      spinGroups.push_back( SpinGroup( it, end, lineNumber, MAT, MF, MT) );
    }

  } catch( std::exception& e ){
    Log::info( "Encountered error while parsing ENDF R-Matrix Limited" );
    throw e;
  }
}
