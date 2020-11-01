//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
ChargedParticleElasticScattering() = default;
#endif

private:
/**
 *  @brief Private constructor
 */
ChargedParticleElasticScattering( InterpolationRecord&& interpolation,
                                  std::vector< Variant >&& sequence ) :
  data_( std::move( interpolation ), std::move( sequence ) ) {}

public:
/**
 *  @brief Constructor
 *
 *  @param[in] spin             the spin of the charged particle
 *  @param[in] lidp             the identicle particle flag
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] distributions    the data for each incident energy value
 */
ChargedParticleElasticScattering ( double spin, long lidp,
                                   std::vector< long >&& boundaries,
                                   std::vector< long >&& interpolants,
                                   std::vector< Variant >&& distributions )
  try : ChargedParticleElasticScattering(
          InterpolationRecord( spin, 0.0, lidp, 0,
                               std::move( boundaries ),
                               std::move( interpolants ) ),
          std::move( distributions ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing charged particle elastic "
               "scattering distribution data (LAW=5)" );
    throw;
  }

private:
/**
 *  @brief Private constructor
 */
template< typename Iterator >
ChargedParticleElasticScattering( InterpolationRecord&& interpolation,
                                  Iterator& begin,
                                  const Iterator& end,
                                  long& lineNumber,
                                  int MAT,
                                  int MF,
                                  int MT ) :
  ChargedParticleElasticScattering( std::move( interpolation ),
                                    readSequence( interpolation.NZ(),
                                                  begin, end, lineNumber,
                                                  MAT, MF, MT ) ) {}

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
ChargedParticleElasticScattering ( Iterator& begin,
                                   const Iterator& end,
                                   long& lineNumber,
                                   int MAT,
                                   int MF,
                                   int MT )
  try : ChargedParticleElasticScattering(
          InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ),
          begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing charged particle elastic "
               "scattering distribution data (LAW=5)" );
    throw;
  }
