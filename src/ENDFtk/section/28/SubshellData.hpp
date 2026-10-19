/**
 *  @class
 *  @brief The subshell data
 *
 *  See ENDF102, section 28.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT SubshellData : protected ListRecord {

  /* auxiliary functions */

  static std::vector< double >
  generateList( double ebi, double eln ) {

    std::vector< double > list = { ebi, eln, 0., 0., 0., 0. };
    return list;
  }

  static std::vector< double >
  generateList( double ebi, double eln,
                std::vector< unsigned int >&& secondary,
                std::vector< unsigned int >&& tertiary,
                std::vector< double >&& energies,
                std::vector< double >&& probabilities ) {

    unsigned int ntr = secondary.size();
    if ( ( tertiary.size() != ntr ) or ( energies.size() != ntr ) or
         ( probabilities.size() != ntr ) ) {

      Log::info( "The number of transitions and the transition data are not "
                 "consistent" );
      Log::info( "NTR value: {}", ntr );
      Log::info( "secondary.size(): {}", secondary.size() );
      Log::info( "tertiary.size(): {}", tertiary.size() );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "probabilities.size(): {}", probabilities.size() );
      throw std::exception();
    }

    std::vector< double > list = generateList( ebi, eln );
    for ( unsigned int i = 0; i < ntr; ++i ) {

      list.push_back( secondary[i] );
      list.push_back( tertiary[i] );
      list.push_back( energies[i] );
      list.push_back( probabilities[i] );
      list.push_back( 0. );
      list.push_back( 0. );
    }
    return list;
  }

  static void
  verifySize( int NPL, int NTR ) {

    if ( NPL != ( NTR + 1 ) * 6 ) {

      Log::error( "Encountered illegal NPL and NTR values " );
      Log::info( "NPL must be equal to 6*NTR+6 for fission yield data" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NTR value: {}", NTR );
      throw std::exception();
    }
  }

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 6 + i )
                              | std23::views::stride( 6 );
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  SubshellData( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifySize( ListRecord::NPL(), this->NTR() );
  };

public:

  #include "ENDFtk/section/28/SubshellData/Transition.hpp"

  /* constructor */

  /**
   *  @brief Constructor without transitions
   *
   *  @param[in] subshell        the subshell designator
   *  @param[in] energy          the binding energy of the subshell
   *  @param[in] eln             the number of electrons in the subshell
   */
  SubshellData( unsigned int subshell, double energy, double eln )
    try : SubshellData(
              ListRecord( subshell, 0.0, 0, 0, 0,
                          generateList( energy, eln ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing subshell data" );
      throw;
    }

  /**
   *  @brief Constructor
   *
   *  @param[in] subshell        the subshell designator
   *  @param[in] energy          the binding energy of the subshell
   *  @param[in] eln             the number of electrons in the subshell
   *  @param[in] secondary       the secondary subshell designators (NTR values)
   *  @param[in] tertiary        the tertiary subshell designators (NTR values)
   *  @param[in] energies        the transition energies (NTR values)
   *  @param[in] probabilities   the transition probabilities (NTR values)
   */
  SubshellData( unsigned int subshell, double energy, double eln,
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

  /* get methods */

  /**
   *  @brief Return the subshell designator
   */
  unsigned int SUBI() const {

    return static_cast< unsigned int >( std::round( ListRecord::C1() ) );
  }

  /**
   *  @brief Return the subshell designator
   */
  unsigned int subshellDesignator() const { return this->SUBI(); }

  /**
   *  @brief Return the number of transitions
   */
  unsigned int NTR() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of transitions
   */
  unsigned int numberTransitions() const { return this->NTR(); }

  /**
   *  @brief Return the subshell binding energy
   */
  double EBI() const { return ListRecord::list()[0]; }

  /**
   *  @brief Return the subshell binding energy
   */
  double subshellBindingEnergy() const { return this->EBI(); }

  /**
   *  @brief Return the number of electrons in the subshell
   */
  double ELN() const { return ListRecord::list()[1]; }

  /**
   *  @brief Return the number of electrons in the subshell
   */
  double numberSubshellElectrons() const { return this->ELN(); }

  /**
   *  @brief Return the secondary subshell designators (one for each transition)
   */
  auto SUBJ() const { return this->column( 0 ); }

  /**
   *  @brief Return the secondary subshell designators (one for each transition)
   */
  auto secondarySubshellDesignators() const { return this->SUBJ(); }

  /**
   *  @brief Return the tertiary subshell designators (one for each transition)
   */
  auto SUBK() const { return this->column( 1 ); }

  /**
   *  @brief Return the tertiary subshell designators (one for each transition)
   */
  auto tertiarySubshellDesignators() const { return this->SUBK(); }

  /**
   *  @brief Return the transition energies
   */
  auto ETR() const { return this->column( 2 ); }

  /**
   *  @brief Return the transition energies
   */
  auto transitionEnergies() const { return this->ETR(); }

  /**
   *  @brief Return the transition probabilities
   */
  auto FTR() const { return this->column( 3 ); }

  /**
   *  @brief Return the transition probabilities
   */
  auto transitionProbabilities() const { return this->FTR(); }

  /**
   *  @brief Return the transitions
   */
  auto transitions() const {

    using namespace njoy::tools;
    using Chunk = decltype( ( ListRecord::list() | std23::views::chunk( 6 ) )[0] );
    return ListRecord::list() | std23::views::chunk( 6 )
             | std20::views::transform(
                 [] ( Chunk&& chunk ) -> Transition< Chunk >
                    { return { std::move( chunk ) }; } )
             | std20::views::drop( 1 );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
