private:
/**
 *  @brief Private intermediate constructor
 */
LValue( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifySize( this->NPL(), this->N2() );
  zeros_ = std::vector( this->NJS(), 0.0 );
}

public:

/**
 *  @brief Constructor
 *
 *  @param[in] awri       the atomic weight ratio
 *  @param[in] l          the orbital angular momentum value
 *  @param[in] spins      the spin values (NJS values)
 *  @param[in] spacing    the level spacing values (NJS values)
 *  @param[in] amun       the degrees of freedom for the neutron width (NJS
 *                        values)
 *  @param[in] gn         the average neutron widths (NJS values)
 *  @param[in] gg         the average gamma widths (NJS values)
 */
LValue( double awri, int l,
        std::vector< double >&& spins,
        std::vector< double >&& spacing,
        std::vector< int >&& amun,
        std::vector< double >&& gn,
        std::vector< double >&& gg )
  try :  LValue( ListRecord( awri, 0.0, l, 0.0, spins.size(),
                             generateList( std::move( spins ),
                                           std::move( spacing ),
                                           std::move( amun ),
                                           std::move( gn ),
                                           std::move( gg ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing l value resonance "
               "parameters in the unresolved Single Level Breit-Wigner "
               "representation" );
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
LValue( Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT )
  try : LValue( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing l value resonance "
               "parameters in the unresolved Single Level Breit-Wigner "
               "representation" );
    throw;
  }
