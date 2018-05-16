EnergyOutgoingCosineDistribution( double energy,
                                  std::vector< long >&& boundaries,
                                  std::vector< long >&& interpolants,
                                  std::vector< CosineOutgoingEnergyDistribution >&& cosines ) :
  InterpolationSequenceRecord( InterpolationRecord( 0.0, energy, 0, 0,
                                                    std::move( boundaries ),
                                                    std::move( interpolants ) ),
                                                    std::move( cosines ) ) {};

template< typename Iterator >
EnergyOutgoingCosineDistribution( Iterator& it, const Iterator& end, long& lineNumber,
                                  int MAT, int MF, int MT ) :
  InterpolationSequenceRecord( it, end, lineNumber, MAT, MF, MT ) {}
