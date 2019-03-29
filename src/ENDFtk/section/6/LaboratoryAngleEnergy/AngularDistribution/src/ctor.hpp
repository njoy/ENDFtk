AngularDistribution(
    double energy,
    std::vector< long >&& boundaries,
    std::vector< long >&& interpolants,
    std::vector< EnergyDistribution >&& cosines ) :
  InterpolationSequenceRecord( InterpolationRecord( 0.0, energy, 0, 0,
                                                    std::move( boundaries ),
                                                    std::move( interpolants ) ),
                                                    std::move( cosines ) ) {};

template< typename Iterator >
AngularDistribution( Iterator& it, const Iterator& end,
                                  long& lineNumber, int MAT, int MF, int MT ) :
  InterpolationSequenceRecord( it, end, lineNumber, MAT, MF, MT ) {}
