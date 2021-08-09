private:
/**
 *  @brief Private intermediate constructor
 *
 *  The number of values in the list should be 2 * 3 or 2 * 17, this is checked.
 */
AverageDecayEnergies( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifyNC( this->numberDecayEnergies() );
}

public:

/**
 *  @brief Constructor
 *
 *  The number of decay energies must be either 3 or 17, this is checked.
 *
 *  @param[in] halflife   the half life and its associated uncertainty
 *  @param[in] energies   the decay energies and uncertainties for the various
 *                        radiation types (either 3 or 17 pairs)
 */
AverageDecayEnergies( std::array< double, 2 > halflife,
                      std::vector< std::array< double, 2 > >&& energies )
  try : AverageDecayEnergies( ListRecord( halflife[0], halflife[1], 0, 0, 0,
                                          generateList( std::move( energies ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing average decay energy "
               "data" );
    throw;
  }

/**
 *  @brief Constructor
 *
 *  This empty constructor is used for a stable nuclide.
 */
AverageDecayEnergies() :
  AverageDecayEnergies( ListRecord( 0.0, 0.0, 0, 0, 0,
                                    { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ) ) {}

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
                      int MAT, int MF, int MT )
  try : AverageDecayEnergies( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading average decay energy data" );
    throw;
  }
