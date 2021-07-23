//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
RectangularMatrix() = default;
#endif

/**
 *  @brief From list.
 *
 *  Needs to be public for read from Subsection.
 */
RectangularMatrix( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLB( this->LB() );
    verifySize( this->NT(), this->NER() );
};

/**
 *  @brief Constructor (LB=5)
 *
 *  @param[in] ls               symmetry flag (0=asymmetric, 1=symmetric)
 *  @param[in] rowEnergies      row energies
 *  @param[in] columnEnergies   column energies
 *  @param[in] values           matrix values
 */
RectangularMatrix( std::vector< double >&& rowEnergies,
                   std::vector< double >&& columnEnergies,
                   std::vector< double >&& values )
try :
  RectangularMatrix(
    ListRecord( 0.0, 0.0, 0, 6, rowEnergies.size(),
                generateList( std::move( rowEnergies ),
                              std::move( columnEnergies ),
                              std::move( values ) ) ) ) {

} catch ( std::exception& e ) {

  Log::info( "Encountered error while constructing RectangularMatrix component" );
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
RectangularMatrix( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
try :
  RectangularMatrix(
    ListRecord( it, end, lineNumber,
                MAT, MF, MT ) ) {

} catch ( std::exception& e ) {

  Log::info( "Encountered error while constructing RectangularMatrix component" );
  throw;
}
