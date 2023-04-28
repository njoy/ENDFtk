//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
DerivedRatioToStandard() = default;
#endif

/**
 *  @brief Cascade for buffer iterator
 *
 *  Needs to be public for reading from Subsection.
 *
 */
template< typename Iterator >
DerivedRatioToStandard( int LTY,
                  Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT ) :
  lty_( LTY ),
  list_( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {

    verifyLTY( this->LTY() );
  }

/**
 *  @brief Constructor
 *
 *  @param[in] lty            covariance procedure
 *  @param[in] e1             lower energy
 *  @param[in] e2             upper energy
 *  @param[in] mats           standard's material number
 *  @param[in] mts            standard's MT number
 *  @param[in] xmfs           standard's MF number
 *  @param[in] xlfss          standard's final excited state
 *  @param[in] energies       energy boundaries of intervals
 *  @param[in] weights        weights of energies
 */
DerivedRatioToStandard( int lty, double e1, double e2,
                  int mats, int mts, int xmfs, int xlfss,
                  std::vector< double >&& energies,
                  std::vector< double >&& weights )
try :
  lty_( lty ),
  list_(
    ListRecord( e1, e2, mats, mts, energies.size(),
                generateList( xmfs, xlfss,
                              std::move( energies ),
                              std::move( weights ) ) ) ) {

} catch ( std::exception& e ) {

  Log::info( "Encountered error while constructing DerivedRatioToStandard component" );
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
DerivedRatioToStandard( Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT )
try :
  DerivedRatioToStandard(
    ControlRecord( it, end, lineNumber, MAT, MF, MT ).L2(),
    it, end, lineNumber, MAT, MF, MT ) {

} catch ( std::exception& e ) {

  Log::info( "Encountered error while constructing DerivedRatioToStandard component" );
  throw;
}
