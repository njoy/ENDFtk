/**
 *  @class
 *  @brief Charged particle elastic scattering given as nuclear amplitude
 *         expansion
 *
 *  See ENDF102, section 6.2.6 for more information.
 */
class NuclearAmplitudeExpansion : protected ListRecord {

  /* auxiliary functions */

  static void
  verifyLTP( int LTP ) {

    if ( LTP != 1 ) {

      Log::error( "Encountered illegal LTP value" );
      Log::info( "LTP must be equal to 1 for nuclear amplitude expansion" );
      Log::info( "LTP value: {}", LTP );
      throw std::exception();
    }
  }

  static void
  verifySize( int NW, int NL ) {

    if ( ( NW != 3 * NL + 3 ) and ( NW != 4 * NL + 3 ) ) {

      Log::error( "Encountered illegal NW and NL values" );
      Log::info( "NW must be equal to 3*NL+3 or 4*NL+3 for "
                 "nuclear amplitude expansion" );
      Log::info( "NW value: {}", NW );
      Log::info( "NL value: {}", NL );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( unsigned int NL,
                std::vector< double >&& b,
                std::vector< double >&& ar,
                std::vector< double >&& ai ) {

    if ( ar.size() != NL + 1 ) {

      Log::info( "The number of real values for a must be equal to NL + 1" );
      Log::info( "NL value: {}", NL );
      Log::info( "ar.size(): {}", ar.size() );
      throw std::exception();
    }
    if ( ai.size() != NL + 1 ) {

      Log::info( "The number of imaginary values for a must be equal to NL + 1" );
      Log::info( "NL value: {}", NL );
      Log::info( "ai.size(): {}", ai.size() );
      throw std::exception();
    }
    if ( not ( ( b.size() == NL + 1 ) or ( b.size() == 2 * NL + 1 ) ) ) {

      Log::info( "The number of b values must be equal to NL + 1 of 2*NL + 1 "
                 "for nuclear amplitude expansion" );
      Log::info( "NL value: {}", NL );
      Log::info( "b.size(): {}", b.size() );
      throw std::exception();
    }

    std::vector< double > list( b );
    for ( unsigned int i = 0; i < NL + 1; ++i ) {

      list.push_back( ar[i] );
      list.push_back( ai[i] );
    }
    return list;
  }

  static std::vector< double >
  generateList( unsigned int NL,
                std::vector< double >&& b,
                std::vector< std::complex< double > >&& a ) {

    if ( a.size() != NL + 1 ) {

      Log::info( "The number of values for a must be equal to NL + 1" );
      Log::info( "NL value: {}", NL );
      Log::info( "a.size(): {}", a.size() );
      throw std::exception();
    }
    if ( ! ( ( b.size() == NL + 1 ) or ( b.size() == 2 * NL + 1 ) ) ) {

      Log::info( "The number of b values must be equal to NL + 1 of 2*NL + 1 "
                 "for nuclear amplitude expansion" );
      Log::info( "NL value: {}", NL );
      Log::info( "b.size(): {}", b.size() );
      throw std::exception();
    }

    std::vector< double > list( b );
    for ( const auto& value : a ) {

      list.push_back( value.real() );
      list.push_back( value.imag() );
    }
    return list;
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  NuclearAmplitudeExpansion( double energy, int nl,
                             std::vector< double >&& list )
    try : NuclearAmplitudeExpansion( ListRecord( 0.0, energy, 1, 0,
                                                 nl, std::move( list ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing nuclear amplitude "
                 "expansion data (LAW=5 LTP=1)" );
      throw;
    }

public:
  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  NuclearAmplitudeExpansion() = default;
  #endif

  /**
   *  @brief Private constructor
   */
  NuclearAmplitudeExpansion( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

      verifyLTP( this->L1() );
      verifySize( this->NW(), this->NL() );
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] energy    the incident energy value
   *  @param[in] nl        the Legendre order
   *  @param[in] b         the coefficients for expanding the nuclear scattering
   *                       cross section
   *  @param[in] a_real    the real component of the a coefficients
   *  @param[in] a_imag    the imaginary component of the a coefficients
   */
  NuclearAmplitudeExpansion( double energy, int nl,
                             std::vector< double >&& b,
                             std::vector< double >&& a_real,
                             std::vector< double >&& a_imag )
    try : NuclearAmplitudeExpansion(
            ListRecord( 0.0, energy, 1, 0, nl,
                        generateList( nl, std::move ( b ),
                                      std::move ( a_real ),
                                      std::move ( a_imag ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing nuclear amplitude "
                 "expansion data (LAW=5 LTP=1)" );
      throw;
    }

  /**
   *  @brief Constructor
   *
   *  @param[in] energy    the incident energy value
   *  @param[in] nl        the Legendre order
   *  @param[in] b         the scattering coefficients (for expanding the nuclear
   *                       scattering cross section)
   *  @param[in] a         the interference coefficients (for expanding the
   *                       nuclear scattering amplitude matrix)
   */
  NuclearAmplitudeExpansion( double energy, int nl,
                             std::vector< double >&& b,
                             std::vector< std::complex< double > >&& a )
    try : NuclearAmplitudeExpansion(
            ListRecord( 0.0, energy, 1, 0, nl,
                        generateList( nl, std::move ( b ),
                                      std::move ( a ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing nuclear amplitude "
                 "expansion data (LAW=5 LTP=1)" );
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
  NuclearAmplitudeExpansion( Iterator& it, const Iterator& end, long& lineNumber,
                             int MAT, int MF, int MT )
    try : NuclearAmplitudeExpansion( ListRecord( it, end, lineNumber,
                                                 MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading nuclear amplitude expansion "
                 "data (LAW=5 LTP=1)" );
      throw;
    }

  /* methods */

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
  static constexpr int LTP() { return 1; }

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
   *  @brief Return the interference coefficients (for expanding the nuclear
   *         scattering cross section)
   */
  auto B() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::take( this->NW() - 2 * this->NL() - 2 );
  }

  /**
   *  @brief Return the interference coefficients (for expanding the nuclear
   *         scattering cross section)
   */
  auto scatteringCoefficients() const { return this->B(); }

  /**
   *  @brief Return the real component of the interference coefficients
   */
  auto AR() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( this->NW() - 2 * this->NL() - 2 )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the real component of the interference coefficients
   */
  auto realInterferenceCoefficients() const { return this->AR(); }

  /**
   *  @brief Return the imaginary component of the interference coefficients
   */
  auto AI() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( this->NW() - 2 * this->NL() - 1 )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the imaginary component of the interference coefficients
   */
  auto imaginaryInterferenceCoefficients() const { return this->AI(); }

  /**
   *  @brief Return the interference coefficients (for expanding the
   *         nuclear scattering amplitude matrix)
   */
  auto A() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( this->NW() - 2 * this->NL() - 2 )
                              | std23::views::chunk( 2 )
                              | std20::views::transform(
                                  [] ( auto&& pair )
                                     { return std::complex< double >( pair[0], pair[1] ); } );
  }

  /**
   *  @brief Return the interference coefficients (for expanding the
   *         nuclear scattering amplitude matrix)
   */
  auto interferenceCoefficients() const { return this->A(); }

  using ListRecord::NC;
  using ListRecord::print;
};
