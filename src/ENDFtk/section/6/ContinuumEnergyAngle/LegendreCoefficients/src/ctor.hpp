LegendreCoefficients( double energy, long nd, long na, long nep,
                      std::vector< double >&& list )
  try : Base( energy, nd, na, nep, std::move( list ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing Legendre coefficients "
               "(LAW=1 LANG=1)" );
    throw;
  }

LegendreCoefficients( double energy, long nd, long na, long nep,
                      std::vector< double > energies,
                      std::vector< std::vector< double > >&& coefficients )
  try : Base( energy, nd, na, nep,
              generateList( na, std::move( energies ),
              std::move( coefficients ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing Legendre coefficients "
               "(LAW=1 LANG=1)" );
    throw;
  }

template< typename Iterator >
LegendreCoefficients( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
  try : Base( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading Legendre coefficients "
               "(LAW=1 LANG=1)" );
    throw;
  }
