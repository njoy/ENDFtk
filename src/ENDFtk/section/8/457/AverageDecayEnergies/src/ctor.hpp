/** 
 *  @brief Constructor
 *
 *  The number of values in the list should be 2 * 3 or 2 * 17, this is checked.
 *
 *  @param[in] list   the ListRecord to be moved into the object
 */
AverageDecayEnergies( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyNC( this->numberDecayEnergies() );
};

/** 
 *  @brief Constructor
 *
 *  The number of decay energies must be either 3 or 17, this is checked.
 *
 *  @param[in] halfLife   the half life and its associated uncertainty
 *  @param[in] energies   the decay energies and uncertainties for the various
 *                        radiation types (either 3 or 17 pairs)
 */
AverageDecayEnergies( std::tuple< double, double > halfLife,
                      std::vector< std::tuple< double, double > >&& energies ) :
  AverageDecayEnergies( ListRecord( std::get< 0 >( halfLife ),
                                    std::get< 1 >( halfLife ), 0, 0, 0,
                                    generateList( std::move( energies ) ) ) ) {};

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
AverageDecayEnergies( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT ) :
  AverageDecayEnergies( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
