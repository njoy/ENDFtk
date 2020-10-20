/**
 *  @brief Constructor
 *
 *  @param[in] awri       the atomic weight ratio
 *  @param[in] apl        the l dependent scattering radius
 *  @param[in] l          the orbital angular momentum value
 *  @param[in] energies   the resonance energies (NRS values)
 *  @param[in] spins      the spin values (NRS values)
 *  @param[in] gn         the neutron widths (NRS values)
 *  @param[in] gg         the gamma widths (NRS values)
 *  @param[in] gfa        the first fission widths (NRS values)
 *  @param[in] gfb        the second fission widths (NRS values)
 */
ReichMooreLValue( double awri, double apl, int l,
                  std::vector< double >&& energies,
                  std::vector< double >&& spins,
                  std::vector< double >&& gn,
                  std::vector< double >&& gg,
                  std::vector< double >&& gfa,
                  std::vector< double >&& gfb )
  try : BreitWignerReichMooreLValueBase( awri, apl, l, false,
                                         std::move( energies ),
                                         std::move( spins ),
                                         std::move( gn ),
                                         std::move( gg ),
                                         std::move( gfa ),
                                         std::move( gfb ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing l value resonance "
               "parameters in the Reich-Moore representation" );
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
ReichMooreLValue( Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT )
  try : BreitWignerReichMooreLValueBase( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing l value resonance "
               "parameters in the Reich-Moore representation" );
    throw;
  }

