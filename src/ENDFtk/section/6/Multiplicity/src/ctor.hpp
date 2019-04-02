Multiplicity( double zap, double awp, long lip, long law,
              std::vector< long >&& boundaries,
              std::vector< long >&& interpolants,
              std::vector< double >&& energies,
              std::vector< double >&& multiplicity )
  try : TabulationRecord( zap, awp, lip, law,
                          std::move( boundaries ),
                          std::move( interpolants ),
                          std::move( energies ),
                          std::move( multiplicity ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing Multiplicity" );
    throw;
  }

template< typename Iterator >
Multiplicity( Iterator& begin, const Iterator& end,
              long& lineNumber, int MAT, int MF, int MT )
  try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading Multiplicity" );
    throw;
  }

