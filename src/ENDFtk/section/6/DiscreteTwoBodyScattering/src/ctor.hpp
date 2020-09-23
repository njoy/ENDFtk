private:
/**
 *  @brief Private constructor
 */
DiscreteTwoBodyScattering ( InterpolationRecord&& interpolation,
                            std::vector< Variant >&& sequence ) :
  data_( std::move( interpolation ), std::move( sequence ) ) {}

public:
/**
 *  @brief Constructor
 *
 *  @param[in] boundaries     the interpolation range boundaries
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] sequence       the data for each incident energy value
 */
DiscreteTwoBodyScattering ( std::vector< long >&& boundaries,
                            std::vector< long >&& interpolants,
                            std::vector< Variant >&& sequence )
  try : DiscreteTwoBodyScattering(
          InterpolationRecord( 0.0, 0.0, 0, 0,
                               std::move( boundaries ),
                               std::move( interpolants ) ),
          std::move( sequence ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing discrete two body "
               "scattering distribution data (LAW=2)" );
    throw;
  }

private:
/**
 *  @brief Private constructor
 */
template< typename Iterator >
DiscreteTwoBodyScattering( InterpolationRecord&& interpolation,
                           Iterator& begin,
                           const Iterator& end,
                           long& lineNumber,
                           int MAT,
                           int MF,
                           int MT ) :
  DiscreteTwoBodyScattering( std::move( interpolation ),
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
DiscreteTwoBodyScattering ( Iterator& begin,
                            const Iterator& end,
                            long& lineNumber,
                            int MAT,
                            int MF,
                            int MT )
  try : DiscreteTwoBodyScattering(
          InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ),
          begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing discrete two body "
               "scattering distribution data (LAW=2)" );
    throw;
  }
