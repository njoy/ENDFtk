SectionBase( double ZA, double AWR, int MT,
             int NL, int NZ, int LRFLAG, int NGN ) :
  Base( ZA, AWR, MT ),
  num_legendre_(NL),
  num_dilutions_(NZ),
  breakup_(LRFLAG),
  num_groups_(NGN)
{}

SectionBase( const HEAD& head ) :
  SectionBase( head.ZA(), head.atomicWeightRatio(), head.MT(),
               head.L1(), head.L2(), head.N1(), head.N2() )
{}
