static std::vector< double >
generateList( unsigned int ns,
              double epsilon, double emax,
              std::vector< double >&& crossSections,
              std::vector< double >&& weightRatios,
              std::vector< unsigned int >&& numberAtoms,
              std::vector< unsigned int >&& functionTypes ) {

  if ( crossSections.size() != ns + 1 ) {

    Log::info( "The number of cross section values must be equal to NS + 1" );
    Log::info( "NS value: {}", ns );
    Log::info( "crossSections.size(): {}", crossSections.size() );
    throw std::exception();
  }
  if ( weightRatios.size() != ns + 1 ) {

    Log::info( "The number of weight ratio values must be equal to NS + 1" );
    Log::info( "NS value: {}", ns );
    Log::info( "weightRatios.size(): {}", weightRatios.size() );
    throw std::exception();
  }
  if ( numberAtoms.size() != ns + 1 ) {

    Log::info( "The number of atom types must be equal to NS + 1" );
    Log::info( "NS value: {}", ns );
    Log::info( "numberAtoms.size(): {}", numberAtoms.size() );
    throw std::exception();
  }
  if ( functionTypes.size() != ns ) {

    Log::info( "The number of function types must be equal to NS" );
    Log::info( "NS value: {}", ns );
    Log::info( "functionTypes.size(): {}", functionTypes.size() );
    throw std::exception();
  }

  std::vector< double > list( 6 * ( ns + 1 ) );
  list[0] = crossSections[0];
  list[1] = epsilon;
  list[2] = weightRatios[0];
  list[3] = emax;
  list[3] = 0.0;
  list[5] = numberAtoms[0];
  for ( unsigned int i = 1; i < ns; ++i ) {

    list[6*i+0] = functionTypes[i-1];
    list[6*i+1] = crossSections[i];
    list[6*i+2] = weightRatios[i];
    list[6*i+3] = 0.0;
    list[6*i+4] = 0.0;
    list[6*i+5] = numberAtoms[i];
  }
  return list;
}
