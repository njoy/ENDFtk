//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
CovariancePairs() = default;
#endif

private:

/**
 *  @brief Private constructor
 */
CovariancePairs( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLB( this->LB(), this->LT() );
    verifySize( this->NT(), this->N2() );
};

public:

/**
 *  @brief Constructor (LB=0,1,2,8,9)
 *
 *  @param[in] lb             the procedure type flag
 *  @param[in] energies       energies
 *  @param[in] fvalues        F values
 */
CovariancePairs( int lb,
                 std::vector< double >&& energies,
                 std::vector< double >&& fvalues )
try :
  CovariancePairs(
    ListRecord( 0.0, 0.0, 0, lb, energies.size(),
                generateList( std::move( energies ),
                              std::move( fvalues ) ) ) ) {

} catch ( std::exception& e ) {

  Log::info( "Encountered error while constructing CovariancePairs component" );
  throw;
}

/**
 *  @brief Constructor (LB=3,4)
 *
 *  @param[in] lb             the procedure type flag
 *  @param[in] ek             first array energies
 *  @param[in] fk             first array F values
 *  @param[in] el             second array energies
 *  @param[in] fl             second array F values
 */
CovariancePairs( int lb,
                 std::vector< double>&& ek,
                 std::vector< double >&& fk,
                 std::vector< double>&& el,
                 std::vector< double >&& fl )
try :
  CovariancePairs(
    ListRecord( 0.0, 0.0, el.size(), lb, ek.size()+el.size(),
                generateList( std::move( ek ),
                              std::move( fk ),
                              std::move( el ),
                              std::move( fl ) ) ) ) {

} catch ( std::exception& e ) {

  Log::info( "Encountered error while constructing CovariancePairs component" );
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
CovariancePairs( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
try :
  CovariancePairs(
    ListRecord( it, end, lineNumber,
                MAT, MF, MT ) ) {

} catch ( std::exception& e ) {

  Log::info( "Encountered error while constructing CovariancePairs component" );
  throw;
}
