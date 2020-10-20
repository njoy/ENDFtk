private:
/**
 *  @brief Private intermediate constructor
 */
JValue( ListRecord&& list ) : ListRecord( std::move( list ) ) {

  verifySize( this->NE() );
}

public:
/**
 *  @brief Constructor
 *
 *  @param[in] l          the orbital angular momentum value
 *  @param[in] spin       the spin
 *  @param[in] d          the level spacing
 *  @param[in] amun       the degrees of freedom for the neutron width
 *  @param[in] amuf       the degrees of freedom for the fission width
 *  @param[in] gn         the average neutron width
 *  @param[in] gg         the average gamma width
 *  @param[in] gf         the average fission widths (NE values)
 */
JValue( int l, double spin, double d, int amun, int amuf,
        double gn, double gg, std::vector< double >&& gf )
  try :  JValue( ListRecord( 0.0, 0.0, l, amuf, 0,
                             generateList( spin, d, amun, gn, gg,
                                           std::move( gf ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing J value resonance "
               "parameters in the unresolved Single Level Breit-Wigner "
               "representation using energy dependent fission widths" );
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
JValue( Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT )
  try : JValue( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing J value resonance "
               "parameters in the unresolved Single Level Breit-Wigner "
               "representation using energy dependent fission widths" );
    throw;
  }
