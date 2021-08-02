//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
DerivedRedundant() = default;
#endif


/**
 *  @brief Cascade for buffer iterator
 *
 *  Needs to be public for reading from Subsection.
 *
 */
template< typename Iterator >
DerivedRedundant( int LTY,
                  Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT ) :
  list_( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {

    verifyLTY( LTY );
  }

/**
 *  @brief Constructor
 *
 *  @param[in] e1             lower energy
 *  @param[in] e2             upper energy
 *  @param[in] coefficients   coefficients to combine linearly
 *  @param[in] reactions      reaction MTs
 */
DerivedRedundant( double e1, double e2,
                  std::vector< double >&& coefficients,
                  std::vector< int >&& reactions )
try :
  list_(
    ListRecord( e1, e2, 0, 0, coefficients.size(),
                generateList( std::move( coefficients ),
                              std::move( reactions ) ) ) ) {

} catch ( std::exception& e ) {

  Log::info( "Encountered error while constructing DerivedRedundant component" );
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
DerivedRedundant( Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT )
try :
  DerivedRedundant(
    ControlRecord( it, end, lineNumber, MAT, MF, MT ).L2(),
    it, end, lineNumber, MAT, MF, MT ) {

} catch ( std::exception& e ) {

  Log::info( "Encountered error while constructing DerivedRedundant component" );
  throw;
}
