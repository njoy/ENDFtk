/**
 *  @class
 *  @brief Charged particle elastic scattering given as nuclear plus
 *         interference distribution
 *
 *  See ENDF102, section 6.2.6 for more information.
 */
class NuclearPlusInterference : protected ListRecord {

  /* auxiliary functions */

  static void
  verifyLTP( int LTP ) {

    if ( ( LTP != 12 ) and ( LTP != 14 ) and ( LTP != 15 ) ) {

      Log::error( "Encountered illegal LTP value" );
      Log::info( "LTP must be equal to 12, 14 or 15 for nuclear "
                 "plus interference");
      Log::info( "LTP value: {}", LTP );
      throw std::exception();
    }
  }

  static void
  verifySize( int NW, int NL ) {

    if ( NW != 2 * NL ) {

      Log::error( "Encountered illegal NW and NL values" );
      Log::info( "NW must be equal to 2 * NL for nuclear plus interference" );
      Log::info( "NW value: {}", NW );
      Log::info( "NL value: {}", NL );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( std::vector< double >&& cosines,
                std::vector< double >&& probabilities ) {

    unsigned int NL = cosines.size();
    if ( cosines.size() != probabilities.size() ) {

      Log::error( "The number of cosine and probability values must be the same" );
      Log::info( "cosines.size(): {}", NL );
      Log::info( "probabilities.size(): {}", probabilities.size() );
      throw std::exception();
    }

    std::vector< double > list;
    for ( unsigned int i = 0; i < NL; ++i ) {

      list.push_back( cosines[i] );
      list.push_back( probabilities[i] );
    }
    return list;
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  NuclearPlusInterference( double energy, long ltp,
                           std::vector< double >&& values )
    try : NuclearPlusInterference( ListRecord( 0.0, energy, ltp, 0,
                                               values.size() / 2,
                                               std::move( values ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing nuclear plus interference "
                 "data (LAW=5 LTP=3)" );
      throw;
    }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  NuclearPlusInterference() = default;
  #endif

  /**
   *  @brief Private constructor
   */
  NuclearPlusInterference( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

      verifyLTP( this->L1() );
      verifySize( this->NW(), this->NL() );
  };

  /**
   *  @brief Constructor
   *
   *  @param[in] energy           the incident energy value
   *  @param[in] ltp              the representation type
   *  @param[in] cosines          the cosine values
   *  @param[in] probabilities    the probability values
   */
  NuclearPlusInterference( double energy, long ltp,
                           std::vector< double >&& cosines,
                           std::vector< double >&& probabilities )
    try : NuclearPlusInterference(
            ListRecord( 0.0, energy, ltp, 0, cosines.size(),
                        generateList( std::move( cosines ),
                                      std::move( probabilities ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing nuclear plus interference "
                 "data (LAW=5 LTP=3)" );
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
  NuclearPlusInterference( Iterator& it, const Iterator& end, long& lineNumber,
                           int MAT, int MF, int MT )
    try : NuclearPlusInterference( ListRecord( it, end, lineNumber,
                                               MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading nuclear plus interference "
                 "data (LAW=5 LTP=3)" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the incident energy
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the representation type
   */
  int LTP() const { return ListRecord::L1(); }

  /**
   *  @brief Return the representation type
   */
  int representation() const { return this->LTP(); }

  /**
   *  @brief Return the number of values in this component
   */
  long NW() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the Legendre order or number of cosine values
   */
  long NL() const { return ListRecord::N2(); }

  /**
   *  @brief Return the cosine values
   */
  auto MU() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const {

    return this->MU();
  }

  /**
   *  @brief Return the probabilities
   */
  auto PNI() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 1 )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the probabilities
   */
  auto probabilities() const {

    return this->PNI();
  }

  using ListRecord::NC;
  using ListRecord::print;
};
