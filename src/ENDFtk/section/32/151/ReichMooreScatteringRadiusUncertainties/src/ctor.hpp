private:
/**
 *  @brief Private intermediate constructor
 */
ReichMooreScatteringRadiusUncertainties( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {}

public:
/**
 *  @brief Constructor
 *
 *  @param[in] dap              the default uncertainty
 *  @param[in] uncertainties    the l-dependent uncertainties
 */
ReichMooreScatteringRadiusUncertainties( double dap,
                                         std::vector< double >&& uncertainties ) :
  // no try ... catch: exceptions will be handled in the derived class
  ReichMooreScatteringRadiusUncertainties(
      ListRecord( 0., 0., 0, 0, 0,
                  generateList( dap, std::move( uncertainties ) ) ) ) {}

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
ReichMooreScatteringRadiusUncertainties( Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT ) :
   // no try ... catch: exceptions will be handled in the derived class
  ReichMooreScatteringRadiusUncertainties(
      ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
