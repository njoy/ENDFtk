/**
 *  @class
 *  @brief Decay constants for delayed neutron precursors at a given incident
 *         energy
 *
 *  See ENDF102, section 1.3 for more information.
 */
class ENDFTK_PYTHON_EXPORT DecayConstants : protected ListRecord {

  /* auxiliary functions */

  static std::vector< double >
  generateList( std::vector< double >&& constants,
                std::vector< double >&& abundances ) {

    auto nnf = constants.size();
    if ( nnf == 0 ) {

      Log::error( "The number of precursor families NNF cannot be zero" );
      throw std::exception();
    }
    if ( nnf != abundances.size() ) {

      Log::error( "The number of precursors and number of abundance values is "
                  "not consistent" );
      Log::info( "NNF value: {}", nnf );
      Log::info( "abundances.size(): {}", abundances.size() );
      throw std::exception();
    }

    std::vector< double > list;
    for ( unsigned int i = 0; i < nnf; ++i ) {

      list.push_back( constants[i] );
      list.push_back( abundances[i] );
    }
    return list;
  }

  static void
  verifySize( int NPL ) {

    if ( ( NPL == 0 ) || ( NPL%2 != 0 ) ) {

      Log::error( "Inconsistent data size" );
      Log::info( "Expected NPL = 2 NNF with NNF > 0" );
      Log::info( "NPL value: {}", NPL );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] energy        the incident neutron energy
   *  @param[in] constants     the precursor families decay constants
   *  @param[in] abundances    the precursor families decay abundances
   */
  DecayConstants( double energy, std::vector< double >&& constants,
                  std::vector< double >&& abundances )
    try : ListRecord( 0.0, energy, 0, 0, 0,
                      generateList( std::move( constants ),
                                    std::move( abundances ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing decay constant data" );
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
  DecayConstants( Iterator& begin, const Iterator& end,
                  long& lineNumber, int MAT, int MF, int MT )
    try : ListRecord( begin, end, lineNumber, MAT, MF, MT ) {

      verifySize( this->NPL() );
    }
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing decay constant data" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int NNF() const { return ListRecord::NPL() / 2; }

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int numberPrecursors() const { return this->NNF(); }

  /**
   *  @brief Return the incident energy value
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy value
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the decay constants
   */
  auto lambdas() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the decay constants
   */
  auto decayConstants() const {

    return this->lambdas();
  }

  /**
   *  @brief Return the abundance values
   */
  auto alphas() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 1 )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the abundance values
   */
  auto abundances() const {

    return this->alphas();
  }

  using ListRecord::NC;
  using ListRecord::print;
};
