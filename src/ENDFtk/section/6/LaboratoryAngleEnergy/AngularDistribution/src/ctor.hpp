AngularDistribution(
    double energy,
    std::vector< long >&& boundaries,
    std::vector< long >&& interpolants,
    std::vector< EnergyDistribution >&& distributions )
  try : InterpolationSequenceRecord(
          InterpolationRecord( 0.0, energy, 0, 0,
                               std::move( boundaries ),
                               std::move( interpolants ) ),
          std::move( distributions ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing angular distribution data "
               "(LAW=7)" );
    throw;
  }

template< typename Iterator >
AngularDistribution( Iterator& it, const Iterator& end,
                                  long& lineNumber, int MAT, int MF, int MT )
  try : InterpolationSequenceRecord(
          readInterpolationSequenceRecord< EnergyDistribution >(
            it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading angular distribution data "
               "(LAW=7)" );
    throw;
  }
