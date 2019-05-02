private:
ContinuumEnergyAngle( InterpolationRecord&& interpolation,
                      std::vector< SubSection >&& sequence ) :
  data_( std::move( interpolation ), std::move( sequence ) ) {

  verifyLANG( this->LANG(), this->data_.records() );
}

public:
ContinuumEnergyAngle( long lep,
                      std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< SubSection >&& sequence )
  try : ContinuumEnergyAngle(
          InterpolationRecord( 0.0, 0.0, sequence.front().LANG(), lep,
                               std::move( boundaries ),
                               std::move( interpolants ) ),
          std::move( sequence ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing continuum energy angle "
               "distribution data (LAW=1)" );
    throw;
  }

private:
template< typename Iterator >
ContinuumEnergyAngle( InterpolationRecord&& interpolation,
                      Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT ) :
  ContinuumEnergyAngle( std::move( interpolation ),
                        readSequence( interpolation.L1(), interpolation.NZ(),
                                      begin, end, lineNumber, MAT, MF, MT ) ) {}

public:
template< typename Iterator >
ContinuumEnergyAngle( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT )
  try : ContinuumEnergyAngle(
          InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ),
          begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading continuum energy angle "
               "distribution data (LAW=1)" );
    throw;
  }
