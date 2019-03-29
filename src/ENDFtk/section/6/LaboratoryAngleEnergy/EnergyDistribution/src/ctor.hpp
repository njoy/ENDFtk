EnergyDistribution( TabulationRecord&& table ) :
  TabulationRecord( std::move( table ) ) {};

EnergyDistribution( double cosine,
                                  std::vector< long >&& boundaries,
                                  std::vector< long >&& interpolants,
                                  std::vector< double >&& energies,
                                  std::vector< double >&& probabilities ) :
  EnergyDistribution(
    TabulationRecord( 0.0, cosine, 0, 0, std::move( boundaries ),
                      std::move( interpolants ), std::move( energies ),
                      std::move( probabilities ) ) ) {};

template< typename Iterator >
EnergyDistribution( Iterator& it, const Iterator& end,
                                  long& lineNumber,
                                  int MAT, int MF, int MT ) :
  EnergyDistribution( TabulationRecord( it, end, lineNumber,
                                    MAT, MF, MT ) ) {}
