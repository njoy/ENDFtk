LaboratoryAngleEnergy(
    std::vector< long >&& boundaries,
    std::vector< long >&& interpolants,
    std::vector< AngularDistribution >&& distributions )
  try : data_( InterpolationRecord( 0.0, 0.0, 0, 0,
                                    std::move( boundaries ),
                                    std::move( interpolants ) ),
                                    std::move( distributions ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing laboratory angle energy "
               "distribution data (LAW=7)" );
    throw;
  }

template< typename Iterator >
LaboratoryAngleEnergy( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT )
  try : data_(
          readInterpolationSequenceRecord<
            LaboratoryAngleEnergy::AngularDistribution >(
              begin, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading laboratory angle energy "
               "distribution data (LAW=7)" );
    throw;
  }
