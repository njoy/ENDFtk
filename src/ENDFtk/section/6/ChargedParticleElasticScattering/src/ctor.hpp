template< typename Iterator >
ChargedParticleElasticScattering ( Iterator& begin,
                                   const Iterator& end,
                                   long& lineNumber,
                                   int MAT,
                                   int MF,
                                   int MT ) :
  data_( begin, end, lineNumber, MAT, MF, MT  ) {}

