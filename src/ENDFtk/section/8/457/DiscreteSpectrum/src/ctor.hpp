private:
/**
 *  @brief Constructor
 *
 *  The number of values in the list should be less than or equal to 12, this is
 *  checked.
 *
 *  @param[in] list   the ListRecord to be moved into the object
 */
DiscreteSpectrum( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifyNT( this->NT() );
}

public:
/**
 *  @brief Constructor
 *
 *  @param[in] chain        the ENDF decay chain
 *  @param[in] energy       the energy and uncertainty
 *  @param[in] intensity    the relative intensity and uncertainty
 *  @param[in] type         the transition type
 */
DiscreteSpectrum( double chain,
                  const std::array< double, 2 >& energy,
                  const std::array< double, 2 >& intensity,
                  double type ) :
  // this can never fail, try-catch would be unreachable
  DiscreteSpectrum(
        ListRecord( energy[0], energy[1], 0, 0, 0,
                    generateList( chain, type, intensity ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] chain        the ENDF decay chain
 *  @param[in] energy       the energy and uncertainty
 *  @param[in] intensity    the relative intensity and uncertainty
 *  @param[in] type         the transition type
 *  @param[in] ris          internal pair formation coefficient or
 *                          positron intensity
 */
DiscreteSpectrum( double chain,
                  const std::array< double, 2 >& energy,
                  const std::array< double, 2 >& intensity,
                  double type,
                  const std::array< double, 2 >& ris ) :
  // this can never fail, try-catch would be unreachable
  DiscreteSpectrum(
        ListRecord( energy[0], energy[1], 0, 0, 0,
                    generateList( chain, type,
                                  intensity,
                                  ris ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] chain        the ENDF decay chain
 *  @param[in] energy       the energy and uncertainty
 *  @param[in] intensity    the relative intensity and uncertainty
 *  @param[in] type         the transition type
 *  @param[in] ris          internal pair formation coefficient or
 *                          positron intensity
 *  @param[in] ricc         the total internal conversion coefficient
 *  @param[in] rick         the K shell internal conversion coefficient
 *  @param[in] ricl         the L shell internal conversion coefficient
 */
DiscreteSpectrum( double chain,
                  const std::array< double, 2 >& energy,
                  const std::array< double, 2 >& intensity,
                  double type,
                  const std::array< double, 2 >& ris,
                  const std::array< double, 2 >& ricc,
                  const std::array< double, 2 >& rick,
                  const std::array< double, 2 >& ricl ) :
  // this can never fail, try-catch would be unreachable
  DiscreteSpectrum(
        ListRecord( energy[0], energy[1], 0, 0, 0,
                    generateList( chain, type,
                                  intensity,
                                  ris, ricc, rick, ricl ) ) ) {}

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
DiscreteSpectrum( Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT )
  try : DiscreteSpectrum( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading discrete spectrum data" );
    throw;
  }
