template< typename Iterator >
EnergyDependent ( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT,
                  int MF,
                  int MT )
  try : interpolation_( begin, end, lineNumber, MAT, MF, MT  ),
        lists_( readLists( begin, end, lineNumber, MAT, MF, MT,
        interpolation_.NZ() ) ) {
    verifyNNF( this->lists_ );
  }
  catch ( std::exception& e ) {
    Log::info( "Error encountered while constructing energy dependent decay constants" );
    throw e;
  }

