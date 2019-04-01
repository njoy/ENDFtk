private:
DiscreteTwoBodyScattering (
  InterpolationSequenceRecord< SubSection >&& data ) :
    data_( std::move( data ) ) {}

public:
DiscreteTwoBodyScattering ( std::vector< long >&& boundaries,
                            std::vector< long >&& interpolants,
                            std::vector< SubSection >&& sequence )
  try : DiscreteTwoBodyScattering(
          InterpolationSequenceRecord< SubSection >( 
            InterpolationRecord( 0.0, 0.0, 0, 0,
                                 std::move( boundaries ),
                                 std::move( interpolants ) ),
            std::move( sequence ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing continuum energy angle "
               "distribution data (LAW=2)" );
    throw;
  }

template< typename Iterator >
DiscreteTwoBodyScattering ( Iterator& begin,
                            const Iterator& end,
                            long& lineNumber,
                            int MAT,
                            int MF,
                            int MT )
  try : DiscreteTwoBodyScattering(
          InterpolationSequenceRecord< SubSection >( begin, end, lineNumber,
                                                     MAT, MF, MT  ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading continuum energy angle "
               "distribution data (LAW=2)" );
    throw;
  }
