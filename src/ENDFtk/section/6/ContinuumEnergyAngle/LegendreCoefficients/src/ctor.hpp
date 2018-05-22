using Base::Base;

LegendreCoefficients( double energy, long nd, long na, long nep,
                      std::vector< std::pair< double,
                                              std::vector< double > > >&& data ) :
 Base( energy, nd, na, nep,
       generateList( na, std::move( data ) ) ) {};
