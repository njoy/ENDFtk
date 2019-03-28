ContinuumEnergyAngle(
  InterpolationSequenceRecord< SubSection >&& data ) :
    data_( std::move( data ) ) {

  checkLANG( this->LANG() );
}

ContinuumEnergyAngle( InterpolationRecord&& interpolation,
                      std::vector< SubSection >&& sequence ) :
  ContinuumEnergyAngle(
    InterpolationSequenceRecord< SubSection >( std::move( interpolation ),
                                               std::move( sequence ) ) ) {}

ContinuumEnergyAngle( long lang,
                      long lep,
                      std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< SubSection >&& sequence ) :
  ContinuumEnergyAngle(
    InterpolationRecord( 0.0, 0.0, lang, lep,
                         std::move( boundaries ), std::move( interpolants ) ),
    std::move( sequence ) ) {}

private:
template< typename Iterator >
ContinuumEnergyAngle( InterpolationRecord&& interpolation,
                      Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT ) :
  ContinuumEnergyAngle(
    std::move( interpolation ),
    readSequence( interpolation.L1(), interpolation.NZ(),
                  begin, end, lineNumber, MAT, MF, MT ) ) {}

public:
template< typename Iterator >
ContinuumEnergyAngle( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT ) :
  ContinuumEnergyAngle(
    readInterpolationRecord( begin, end, lineNumber, MAT, MF, MT ),
    begin, end, lineNumber, MAT, MF, MT ) {}

