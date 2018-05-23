DiscreteTwoBodyScattering (
  InterpolationSequenceRecord< SubSection >&& data ) : data_( data ) {}

DiscreteTwoBodyScattering ( InterpolationRecord&& interpolation,
                            std::vector< SubSection >&& sequence ) :
  DiscreteTwoBodyScattering(
    InterpolationSequenceRecord< SubSection >( std::move( interpolation ),
                                               std::move( sequence ) ) ) {}

DiscreteTwoBodyScattering ( std::vector< long >&& boundaries,
                            std::vector< long >&& interpolants,
                            std::vector< SubSection >&& sequence ) :
  DiscreteTwoBodyScattering(
    InterpolationRecord( 0.0, 0.0, 0, 0,
                         std::move( boundaries ), std::move( interpolants ) ),
    std::move( sequence ) ) {}

template< typename Iterator >
DiscreteTwoBodyScattering ( Iterator& begin,
                            const Iterator& end,
                            long& lineNumber,
                            int MAT,
                            int MF,
                            int MT ) :
  DiscreteTwoBodyScattering(
    InterpolationSequenceRecord< SubSection >( begin, end, lineNumber,
                                               MAT, MF, MT  ) ) {}

