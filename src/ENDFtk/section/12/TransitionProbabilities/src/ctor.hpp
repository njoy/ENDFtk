private:

/**
 *  @brief Private constructor
 */
TransitionProbabilities( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifyLG( this->LG() );
}

public:

/**
 *  @brief Constructor (for the simple case, LG = 1)
 *
 *  @param[in] energy          the highest energy level
 *  @param[in] energies        the energy levels below the highest level
 *                             (NT values)
 *  @param[in] probabilities   the transition probabilities (NT values)
 */
TransitionProbabilities( double energy,
                         std::vector< double >&& energies,
                         std::vector< double >&& probabilities )
  try : TransitionProbabilities(
          ListRecord( energy, 0.0, 0, 0, energies.size(),
                     generateList( std::move( energies ),
                                   std::move( probabilities ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing transition probabilities" );
    throw;
  }

/**
 *  @brief Constructor (for the complex case, LG = 2)
 *
 *  @param[in] energy          the highest energy level
 *  @param[in] energies        the energy levels below the highest level
 *                             (NT values)
 *  @param[in] probabilities   the transition probabilities (NT values)
 *  @param[in] conditionals    the conditional photon probabilities (NT values)
 */
TransitionProbabilities( double energy,
                         std::vector< double >&& energies,
                         std::vector< double >&& probabilities,
                         std::vector< double >&& conditionals )
  try : TransitionProbabilities(
          ListRecord( energy, 0.0, 0, 0, energies.size(),
                      generateList( std::move( energies ),
                                    std::move( probabilities ),
                                    std::move( conditionals ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing transition probabilities" );
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
TransitionProbabilities( Iterator& begin, const Iterator& end,
                         long& lineNumber, int MAT, int MF, int MT )
  try : TransitionProbabilities( ListRecord( begin, end, lineNumber,
                                 MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing transition probabilities" );
    throw;
  }
