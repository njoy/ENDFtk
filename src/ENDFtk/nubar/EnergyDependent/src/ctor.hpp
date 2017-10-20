template< typename Iterator >
EnergyDependent ( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT,
                  int MF,
                  int MT )
  try: interpolation_( begin, end, lineNumber, MAT, MF, MT  ),
       lists_( readLists( begin, end, lineNumber, MAT, MF, MT,
               interpolation_.NZ() ) ) {}
  catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File {} of Material {}",
               MT, MF, MAT );
    throw e;
  }

