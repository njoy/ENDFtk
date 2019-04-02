private:
ChargedParticleElasticScattering (
  InterpolationSequenceRecord< SubSection >&& data ) :
    data_( std::move( data ) ) {}

public:
ChargedParticleElasticScattering ( double spin, long lidp,
                                   std::vector< long >&& boundaries,
                                   std::vector< long >&& interpolants,
                                   std::vector< SubSection >&& sequence )
  try : ChargedParticleElasticScattering(
          InterpolationSequenceRecord< SubSection >( 
            InterpolationRecord( spin, 0.0, lidp, 0,
                                 std::move( boundaries ),
                                 std::move( interpolants ) ),
            std::move( sequence ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing charged particle elastic "
               "scattering distribution data (LAW=5)" );
    throw;
  }

template< typename Iterator >
ChargedParticleElasticScattering ( Iterator& begin,
                                   const Iterator& end,
                                   long& lineNumber,
                                   int MAT,
                                   int MF,
                                   int MT )
  try : ChargedParticleElasticScattering(
          InterpolationSequenceRecord< SubSection >( begin, end, lineNumber,
                                                     MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading charged particle elastic "
               "scattering distribution data (LAW=5)" );
    throw;
  }

