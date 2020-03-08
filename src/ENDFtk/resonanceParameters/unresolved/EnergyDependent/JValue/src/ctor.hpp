private:
/**
 *  @brief Private intermediate constructor
 */
JValue( ListRecord&& list ) : ListRecord( std::move( list ) ) {

  verifySize( ListRecord::NPL(), this->NE() );
}

public:
/**
 *  @brief Constructor
 *
 *  @param[in] spin          the spin
 *  @param[in] amun          the degrees of freedom for the neutron width
 *  @param[in] amug          the degrees of freedom for the gamma width
 *  @param[in] amuf          the degrees of freedom for the fission width
 *  @param[in] amux          the degrees of freedom for the competitive width
 *  @param[in] interpolate   the interpolation scheme for the cross sections
 *  @param[in] energies      the energy values (NE values)
 *  @param[in] d             the level spacings (NE values)
 *  @param[in] gn            the average neutron widths (NE values)
 *  @param[in] gg            the average gamma widths (NE values)
 *  @param[in] gf            the average fission widths (NE values)
 *  @param[in] gx            the average competitive widths (NE values)
 */
JValue( double spin, int amun, int amug, int amuf, int amux, int interpolate,
        std::vector< double >&& energies,
        std::vector< double >&& d,
        std::vector< double >&& gn,
        std::vector< double >&& gg,
        std::vector< double >&& gf,
        std::vector< double >&& gx )
  try :  JValue( ListRecord( spin, 0.0, interpolate, 0, energies.size(),
                             generateList( amux, amun, amug, amuf,
                                           std::move( energies ),
                                           std::move( d ),
                                           std::move( gx ),
                                           std::move( gn ),
                                           std::move( gg ),
                                           std::move( gf ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing J value resonance "
               "parameters in the unresolved Single Level Breit-Wigner "
               "representation using energy dependent widths" );
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
               "representation using energy dependent widths" );
    throw;
  }
