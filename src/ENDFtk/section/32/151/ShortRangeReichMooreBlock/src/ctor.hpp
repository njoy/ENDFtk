//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
ShortRangeReichMooreBlock() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] mpar       the number of parameters with covariances
 *  @param[in] energies   the resonance energies (NRB values)
 *  @param[in] spins      the spin values (NRB values)
 *  @param[in] gn         the neutron widths (NRB values)
 *  @param[in] gg         the gamma widths (NRB values)
 *  @param[in] gfa        the first fission widths (NRB values)
 *  @param[in] gfb        the second fission widths (NRB values)
 *  @param[in] values     the values of the upper diagonal covaraince matrix
 */
 ShortRangeReichMooreBlock( int mpar,
                            std::vector< double >&& energies,
                            std::vector< double >&& spins,
                            std::vector< double >&& gn,
                            std::vector< double >&& gg,
                            std::vector< double >&& gfa,
                            std::vector< double >&& gfb,
                            std::vector< double >&& values )
  try : ShortRangeBreitWignerReichMooreBlockBase(
            mpar, std::move( energies ),
            std::move( spins ), std::move( gn ),
            std::move( gg ), std::move( gfa ),
            std::move( gfb ), std::move( values ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing short range resonance and "
               "covariance parameters in the Reich-Moore representation" );
    throw;
  }

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
ShortRangeReichMooreBlock( Iterator& it, const Iterator& end, long& lineNumber,
                           int MAT, int MF, int MT )
  try : ShortRangeBreitWignerReichMooreBlockBase( it, end, lineNumber,
                                                  MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing short range resonance and "
               "covariance parameters in the Reich-Moore representation" );
    throw;
  }
