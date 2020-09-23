private:
/**
 *  @brief Private constructor
 */
ContinuumEnergyAngle( InterpolationRecord&& interpolation,
                      std::vector< Variant >&& sequence ) :
  data_( std::move( interpolation ), std::move( sequence ) ) {

  verifyLANG( this->LANG(), this->data_.records() );
}

public:
/**
 *  @brief Constructor
 *
 *  @param[in] lep            the secondary energy interpolation scheme
 *  @param[in] boundaries     the interpolation range boundaries
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] sequence       the data for each incident energy value
 */
ContinuumEnergyAngle( long lep,
                      std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< Variant >&& sequence )
  try : ContinuumEnergyAngle(
          InterpolationRecord( 0.0, 0.0,
                               std::visit( [] ( const auto& entry )
                                              { return entry.LANG(); },
                                           sequence.front() ),
                               lep,
                               std::move( boundaries ),
                               std::move( interpolants ) ),
          std::move( sequence ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing continuum energy angle "
               "distribution data (LAW=1)" );
    throw;
  }

private:
/**
 *  @brief Private constructor
 */
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
/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] it           the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 *  @param[in] MF           the expected MF number
 *  @param[in] MT           the expected MT number
 */
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
