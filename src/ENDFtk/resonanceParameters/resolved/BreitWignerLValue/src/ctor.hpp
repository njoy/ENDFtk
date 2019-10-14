/**
 *  @brief Constructor
 *
 *  @param[in] awri       the atomic weight ratio
 *  @param[in] qx         the competitive Q value
 *  @param[in] l          the orbital angular momentum value
 *  @param[in] lrx        the competitive width flag
 *  @param[in] energies   the resonance energies (NRS values)
 *  @param[in] spins      the spin values (NRS values)
 *  @param[in] gn         the neutron widths (NRS values)
 *  @param[in] gg         the gamma widths (NRS values)
 *  @param[in] gfa        the first fission widths (NRS values)
 *  @param[in] gfb        the second fission widths (NRS values)
 */
BreitWignerLValue( double awri, double qx, int l, bool lrx,
                   std::vector< double >&& energies,
                   std::vector< double >&& spins,
                   std::vector< double >&& gt,
                   std::vector< double >&& gn,
                   std::vector< double >&& gg,
                   std::vector< double >&& gf )
  // no try ... catch: exceptions will be handled in the derived class
  try : BreitWignerReichMooreLValueBase( awri, qx, l, lrx,
                                         std::move( energies ),
                                         std::move( spins ),
                                         std::move( gt ),
                                         std::move( gn ),
                                         std::move( gg ),
                                         std::move( gf ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing l value resonance "
               "parameters in the Breit-Wigner representation" );
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
BreitWignerLValue( Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT )
  try : BreitWignerReichMooreLValueBase( it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing l value resonance "
               "parameters in the Breit-Wigner representation" );
    throw;
  }

