/**
 *  @brief Constructor
 *
 *  @param[in] qm               the mass difference Q value
 *  @param[in] qi               the reaction Q value
 *  @param[in] izap             the za identifier of the product
 *  @param[in] lfs              the excited level number
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] energies         the energy values
 *  @param[in] xs               the cross section values
 */
ReactionProduct( double qm, double qi, long izap, long lfs,
                 std::vector< long >&& boundaries,
                 std::vector< long >&& interpolants,
                 std::vector< double >&& energies,
                 std::vector< double >&& xs )
  try : TabulationRecord( qm, qi, izap, lfs,
                          std::move( boundaries ),
                          std::move( interpolants ),
                          std::move( energies ),
                          std::move( xs ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a radioactive reaction "
               "product" );
    throw;
  }

/**
 *  @brief Constructor for a single interpolation zone
 *
 *  @param[in] qm             the mass difference Q value
 *  @param[in] qi             the reaction Q value
 *  @param[in] izap           the za identifier of the product
 *  @param[in] lfs            the excited level number
 *  @param[in] energies       the energy values
 *  @param[in] xs             the multiplicities for every state
 *  @param[in] interpolant    the interpolation type (default 2 - linlin)
 */
ReactionProduct( double qm, double qi, long izap, long lfs,
                 std::vector< double >&& energies,
                 std::vector< double >&& xs,
                 long interpolant = 2 ) :
  ReactionProduct( qm, qi, izap, lfs,
                   { static_cast<long>( energies.size() ) }, { interpolant },
                   std::move( energies ), std::move( xs ) ) {}

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
ReactionProduct( Iterator& begin, const Iterator& end,
                 long& lineNumber, int MAT, int MF, int MT )
  try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a radioactive reaction "
               "product" );
    throw;
  }
