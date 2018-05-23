ChargedParticleElasticScattering (
  InterpolationSequenceRecord< SubSection >&& data ) : data_( data ) {}

ChargedParticleElasticScattering ( InterpolationRecord&& interpolation,
                                   std::vector< SubSection >&& sequence ) :
  ChargedParticleElasticScattering(
    InterpolationSequenceRecord< SubSection >( std::move( interpolation ),
                                               std::move( sequence ) ) ) {}

ChargedParticleElasticScattering ( double spin, long lidp,
                                   std::vector< long >&& boundaries,
                                   std::vector< long >&& interpolants,
                                   std::vector< SubSection >&& sequence ) :
  ChargedParticleElasticScattering(
    InterpolationRecord( spin, 0.0, lidp, 0,
                         std::move( boundaries ), std::move( interpolants ) ),
    std::move( sequence ) ) {}

template< typename Iterator >
ChargedParticleElasticScattering ( Iterator& begin,
                                   const Iterator& end,
                                   long& lineNumber,
                                   int MAT,
                                   int MF,
                                   int MT ) :
  ChargedParticleElasticScattering(
    InterpolationSequenceRecord< SubSection >( begin, end, lineNumber,
                                               MAT, MF, MT  ) ) {}

