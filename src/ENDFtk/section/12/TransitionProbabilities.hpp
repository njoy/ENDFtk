/**
 *  @class
 *  @brief The photon production cross section can be calculated from MF3 and
 *         the transition probabilities are given here
 *
 *  The TransitionProbabilities class is used to represent the case in which
 *  the photon production cross sections is computed from the MF3 cross section
 *  and the transition probabilities given here.
 *
 *  See ENDF102, section 12.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT TransitionProbabilities : protected ListRecord {

public:

  #include "ENDFtk/section/12/TransitionProbabilities/Transition.hpp"

private:

  /* auxiliary functions */

  static void
  verifyLG( int LG ) {

    if ( ( LG != 1 ) and ( LG != 2 ) ) {

      Log::error( "Encountered illegal LG value" );
      Log::info( "LG must be equal to 1 (simple case) or 2 (complex case)" );
      Log::info( "LG value: {}", LG );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( std::vector< double >&& energies,
                std::vector< double >&& probabilities ) {

    std::vector< double > list;

    unsigned int NT = energies.size();
    if ( energies.size() != probabilities.size() ) {

      Log::error( "The number of energy and probability values must be the same" );
      Log::info( "energies.size(): {}", NT );
      Log::info( "probabilities.size(): {}", probabilities.size() );
      throw std::exception();
    }

    for ( unsigned int i = 0; i < NT; ++i ) {

      list.push_back( energies[i] );
      list.push_back( probabilities[i] );
    }
    return list;
  }

  static std::vector< double >
  generateList( std::vector< double >&& energies,
                std::vector< double >&& probabilities,
                std::vector< double >&& conditionalProbabilities ) {

    std::vector< double > list;

    unsigned int NT = energies.size();
    if ( ( energies.size() != probabilities.size() ) or
         ( energies.size() != conditionalProbabilities.size() ) ) {

      Log::error( "The number of energy and probability values must be the same" );
      Log::info( "energies.size(): {}", NT );
      Log::info( "probabilities.size(): {}", probabilities.size() );
      Log::info( "conditionalProbabilities.size(): {}",
                 conditionalProbabilities.size() );
      throw std::exception();
    }
    for ( unsigned int i = 0; i < NT; ++i ) {

      list.push_back( energies[i] );
      list.push_back( probabilities[i] );
      list.push_back( conditionalProbabilities[i] );
    }
    return list;
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  TransitionProbabilities( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifyLG( this->LG() );
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  TransitionProbabilities() = default;
  #endif

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

  /* get methods */

  /**
   *  @brief Return the photon production representation type
   */
  static constexpr int LO() { return 2; }

  /**
   *  @brief Return the photon production representation type
   */
  int representation() const { return this->LO(); }

  /**
   *  @brief Return the energy of the highest energy level
   */
  double ES() const { return ListRecord::C1(); }

  /**
  *  @brief Return the energy of the highest energy level
   */
  double highestEnergyLevel() const { return this->ES(); }

  /**
   *  @brief Return the number of transitions that are given
   */
  long NT() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of transitions that are given
   */
  long numberTransitions() const { return this->NT(); }

  /**
   *  @brief Return whether the data is simple (pairs) or complex (triplets)
   */
  int LG() const { return ListRecord::NPL() / this->NT() - 1; }

  /**
   *  @brief Return whether the data is simple (pairs) or complex (triplets)
   */
  int transitionType() const { return this->LG(); }

  /**
   *  @brief Return the data as either pairs (energy, transition probability)
   *         or triplets (energy, transition probability, conditional
   *         probability for photon emission).
   */
  auto transitions() const {

    using namespace njoy::tools;
    auto chunked = ListRecord::list() | std23::views::chunk( this->LG() + 1 );
    using Range = decltype( chunked[0] );
    return chunked | std20::views::transform(
                         [] ( Range&& chunk ) -> Transition< Range >
                            { return { std::move( chunk ) }; } );
  }

  /**
   *  @brief Return the energy values.
   */
  auto E() const {

    using namespace njoy::tools;
    return this->transitions()
             | std20::views::transform( [] ( const auto& transition )
                                           { return transition.E(); } );
  }

  /**
   *  @brief Return the energy values.
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the transition probabilities.
   */
  auto TP() const {

    using namespace njoy::tools;
    return this->transitions()
      | std20::views::transform( [] ( const auto& transition )
                                    { return transition.TP(); } );
  }

  /**
   *  @brief Return the transiition probabilities.
   */
  auto transitionProbabilities() const { return this->TP(); }

  /**
   *  @brief Return the conditional probabilities.
   */
  auto GP() const {

    using namespace njoy::tools;
    return this->transitions()
      | std20::views::transform( [] ( const auto& transition )
                                    { return transition.GP(); } );
  }

  /**
   *  @brief Return the transiition probabilities.
   */
  auto conditionalProbabilities() const { return this->GP(); }

  using ListRecord::NC;
  using ListRecord::print;
};
