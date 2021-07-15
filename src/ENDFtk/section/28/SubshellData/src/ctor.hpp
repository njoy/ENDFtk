private:

/**
 *  @brief Private constructor
 */
SubshellData( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifySize( ListRecord::NPL(), this->NTR() );
};

public:

/**
 *  @brief Constructor
 *
 *  @param[in] subshell        the subshell designator
 *  @param[in] energy          the binding energy of the subshell
 *  @param[in] eln             the number of electrons in the subshell
 *  @param[in] secondary       the secondary subshell designators (NTR values)
 *  @param[in] tertiary        the tertiary subshell designators (NTR values)
 *  @param[in] energies        the transition energies
 *  @param[in] probabilities   the transition probabilities
 */
SubshellData( unsigned int subshell, double energy, unsigned int eln,
              std::vector< unsigned int >&& secondary,
              std::vector< unsigned int >&& tertiary,
              std::vector< double >&& energies,
              std::vector< double >&& probabilities )
  try : SubshellData(
            ListRecord( subshell, 0.0, 0, 0, secondary.size(),
                        generateList( energy, eln,
                                      std::move( secondary ),
                                      std::move( tertiary ),
                                      std::move( energies ),
                                      std::move( probabilities ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing subshell data" );
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
SubshellData( Iterator& begin, const Iterator& end,
                  long& lineNumber, int MAT, int MF, int MT )
  try : SubshellData( ListRecord( begin, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing subshell data" );
    throw;
  }
