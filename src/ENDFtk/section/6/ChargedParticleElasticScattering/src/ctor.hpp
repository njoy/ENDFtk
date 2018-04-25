ChargedParticleElasticScattering (
  InterpolationSequenceRecord< SubSection >&& data ) : data_( data ) {}

ChargedParticleElasticScattering ( InterpolationRecord&& interpolation,
                                   std::vector< SubSection >&& sequence ) :
  ChargedParticleElasticScattering(
    InterpolationSequenceRecord< SubSection >( std::move( interpolation ),
                                               std::move( sequence ) ) ) {}

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

