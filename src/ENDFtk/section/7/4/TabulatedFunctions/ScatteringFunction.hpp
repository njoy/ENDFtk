/**
 *  @class
 *  @brief S(alpha,beta,T) data for a fixed value of beta
 *
 *  The ScatteringFunction class is used to represent the temperature dependent
 *  S(alpha,beta,T) data for a fixed value of beta from ENDF section MF7/MT4.
 *  It contains a grid of alpha values with a corresponding S(T) grid for each
 *  temperature as well as interpolation information as a function of alpha
 *  and temperature.
 *
 *  Note: temperature interpolation of S(alpha,beta) is discouraged.
 *
 *  See ENDF102, section 7.4 for more information.
 */
class ScatteringFunction {

  /* members */

  TabulationRecord alphas_;
  std::vector< ListRecord > temperatures_;

  /* auxiliary functions */

  static std::vector< ListRecord >
  generateTemperatures( double beta,
                        std::vector< double >&& temperatures,
                        std::vector< long >&& li,
                        std::vector< std::vector< double > >&& s ) {
    unsigned int size = temperatures.size() - 1;
    std::vector< ListRecord > sequence;
    sequence.reserve( size );

    if ( ( size != li.size() ) || ( size + 1 != s.size() ) ) {

      Log::error( "Encountered inconsistent number of temperatures, "
                  "interpolation flags and S(a,b) function values" );
      Log::info( "Number of LI values must be equal to NT - 1" );
      Log::info( "Number of S(a,b) sets must be equal to NT" );
      Log::info( "Number of LI values: {}", li.size() );
      Log::info( "Number of S(a,b) sets: {}", s.size() );
      Log::info( "NT value: {}", size + 1 );
      throw std::exception();
    }

    unsigned int i = 0;
    while( i++ < size ){
      sequence.emplace_back( ListRecord( temperatures[i], beta, li[i-1], 0, 0,
                                         std::move( s[i] ) ) );
    }

    return sequence;
  }

  template< typename Array >
  static void
  verifyBetaValues( double beta, const Array& range ) {

    auto compare = [beta] ( const auto& entry )
                          { return entry != beta; };

    auto iter = std::find_if( range.begin(), range.end(), compare );
    bool inconsistent = ( range.end() != iter );
    if ( inconsistent ) {

      Log::error( "Encountered inconsistent beta values within a BetaValue" );
      Log::info( "Expected: {}", beta );
      Log::info( "Found: {}", *iter );
      throw std::exception();
    }
  }

  /* workaround for the removal of range-v3 */

  // range-v3 allowed for concatenation of different ranges but our new capability
  // does not. we therefore generate these arrays at construction time
  using Array = decltype( alphas_.y() );
  std::vector< Array > s_;
  std::vector< double > t_;

  void  generateSandT() {

    this->s_.clear();
    this->t_.clear();

    this->s_.reserve( this->numberTemperatures() );
    this->t_.reserve( this->numberTemperatures() );

    this->s_.emplace_back( this->alphas_.y() );
    this->t_.push_back( this->alphas_.C1() );
    for ( auto&& list : this->temperatures_ ) {

      this->s_.emplace_back( list.list() );
      this->t_.push_back( list.C1() );
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   *
   *  The number of entries in the temperatures array is checked against the
   *  temperature dependence flag LT (the L1 value on the TabulationRecord).
   */
  ScatteringFunction( TabulationRecord&& alphas,
                      std::vector< ListRecord >&& temperatures ) :
    alphas_( std::move( alphas ) ), temperatures_( std::move( temperatures ) ) {

    this->generateSandT();
    if ( this->NT() != 1 ) {
      verifyBetaValues( this->beta(),
                        this->temperatures_ |
                            njoy::tools::std20::views::transform(
                                [] ( const auto& v )
                                   { return v.C2(); } ) );
    }
  }

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  ScatteringFunction( TabulationRecord&& alphas,
                      Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT ) :
    ScatteringFunction( std::move( alphas ),
                        readSequence< ListRecord >( begin, end, lineNumber,
                                                    MAT, MF, MT, alphas.L1() ) ) {}

public:

  /* constructor */

  ScatteringFunction( const ScatteringFunction& f ) :
    alphas_( f.alphas_ ), temperatures_( f.temperatures_ ) {

    this->generateSandT();
  }

  ScatteringFunction( ScatteringFunction&& f ) :
    alphas_( std::move( f.alphas_ ) ), temperatures_( std::move( f.temperatures_ ) ) {

    this->generateSandT();
  }

  /**
   *  @brief Constructor (multiple temperatures)
   *
   *  The size of the various arrays is checked for consistency where appropriate.
   *
   *  @param[in] beta           the beta value for which data will be given
   *  @param[in] boundaries     the interpolation range boundaries for S(a,beta)
   *  @param[in] interpolants   the interpolation types for each range
   *  @param[in] temperatures   the temperatures (NT values)
   *  @param[in] li             the temperature interpolation flags (NT-1 values)
   *  @param[in] alphas         the alpha values (NA values)
   *  @param[in] sab            the thermal scattering values (NT arrays of NA
   *                            values)
   */
  ScatteringFunction( double beta,
                      std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< double >&& temperatures,
                      std::vector< long >&& li,
                      std::vector< double >&& alphas,
                      std::vector< std::vector< double > >&& sab )
    try : ScatteringFunction(
              TabulationRecord( temperatures[0], beta,
                                temperatures.size() - 1, 0,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( alphas ),
                                std::move( sab[0] ) ),
              generateTemperatures( beta,
                                    std::move( temperatures ),
                                    std::move( li ),
                                    std::move( sab ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing S(a,b) data for a given "
                 "beta value" );
      throw;
    }

  /**
   *  @brief Constructor (single temperature)
   *
   *  The size of the various arrays is checked for consistency where appropriate.
   *
   *  @param[in] temperature    the temperature
   *  @param[in] beta           the beta value for which data will be given
   *  @param[in] boundaries     the interpolation range boundaries for S(a,beta)
   *  @param[in] interpolants   the interpolation types for each range
   *  @param[in] alphas         the alpha values (NA values)
   *  @param[in] sab            the thermal scattering values (NA values)
   */
  ScatteringFunction( double temperature, double beta,
                      std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< double >&& alphas,
                      std::vector< double >&& sab )
    try : ScatteringFunction( TabulationRecord( temperature, beta, 0, 0,
                                                std::move( boundaries ),
                                                std::move( interpolants ),
                                                std::move( alphas ),
                                                std::move( sab ) ), {} ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing S(a,b) data for a given "
                 "beta value" );
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
  ScatteringFunction( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT )
    try : ScatteringFunction( TabulationRecord( begin, end, lineNumber,
                                                MAT, MF, MT ),
                              begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing S(a,b) data for a given "
                 "beta value" );
      throw;
    }

  ScatteringFunction& operator=( const ScatteringFunction& base ) {

    if ( this != &base ) {

      this->alphas_ = base.alphas_;
      this->temperatures_ = base.temperatures_;
      this->generateSandT();
    }
    return *this;
  }

  ScatteringFunction& operator=( ScatteringFunction&& base ) {

    if ( this != &base ) {

      this->alphas_ = std::move( base.alphas_ );
      this->temperatures_ = std::move( base.temperatures_ );
      this->generateSandT();
    }
    return *this;
  }

  /* get methods */

  /**
   *  @brief Return the current beta value
   */
  double B() const { return this->alphas_.C2(); }

  /**
   *  @brief Return the current beta value
   */
  double beta() const { return this->B(); }

  /**
   *  @brief Return the LT flag indicating the temperature dependence (equal to
   *         NT - 1)
   */
  int LT() const { return this->alphas_.L1(); }

  /**
   *  @brief Return the LT flag indicating the temperature dependence (equal to
   *         NT - 1)
   */
  int temperatureDependenceFlag() const { return this->LT(); }

  /**
   *  @brief Return the number of temperatures NT for which thermal scattering
   *         law data is given
   */
  int NT() const { return this->temperatures_.size() + 1; }

  /**
   *  @brief Return the number of temperatures NT for which thermal scattering
   *         law data is given
   */
  int numberTemperatures() const { return this->NT(); }

  /**
   *  @brief Return the number of interpolation ranges on the alpha grid
   */
  long NR() const { return this->alphas_.NR(); }

  /**
   *  @brief Return the number of interpolation ranges on the alpha grid
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of alpha values
   */
  long NP() const { return this->alphas_.NP(); }

  /**
   *  @brief Return the number of alpha values
   */
  long numberPoints() const { return this->NP(); }

  /**
   *  @brief Return the number of alpha values
   */
  long NA() const { return this->alphas_.NP(); }

  /**
   *  @brief Return the number of alpha values
   */
  long numberAlphas() const { return this->NA(); }

  /**
   *  @brief Return interpolation type for each range on the alpha grid
   */
  auto INT() const { return this->alphas_.INT(); }

  /**
   *  @brief Return interpolation type for each range on the alpha grid
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return interpolation boundaries for the alpha grid
   */
  auto NBT() const { return this->alphas_.NBT(); }

  /**
   *  @brief Return interpolation boundaries for the alpha grid
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return all temperatures for which thermal scattering law data is
   *         given
   */
  auto T() const {

    using namespace njoy::tools;
    return this->t_ | std20::views::all;
  }

  /**
   *  @brief Return all temperatures for which thermal scattering law data is
   *         given
   */
  auto temperatures() const { return this->T(); }

  /**
   *  @brief Return the alpha grid
   */
  auto A() const { return this->alphas_.x(); }

  /**
   *  @brief Return the alpha grid
   */
  auto alphas() const { return this->A(); }

  /**
   *  @brief Return the temperature interpolation flags (LT values will be
   *         given)
   */
  auto LI() const {

    using namespace njoy::tools;
    return this->temperatures_ | std20::views::transform( [] ( const auto& v )
                                                             { return v.L1(); } );
  }

  /**
   *  @brief Return the temperature interpolation flags (LT values will be
   *         given)
   */
  auto temperatureInterpolants() const { return this->LI(); }

  /**
   *  @brief Return the thermal scattering law values as an array, one for each
   *         temperature
   */
  auto S() const {

    using namespace njoy::tools;
    return this->s_ | std20::views::all;
 }

  /**
   *  @brief Return the thermal scattering law values as an array, one for each
   *         temperature
   */
  auto thermalScatteringValues() const { return this->S(); }

  /**
   *  @brief Return the number of lines in this MF7/MT4 component
   */
  long NC() const {
    long NC = this->alphas_.NC();
    for ( const auto& entry : this->temperatures_ ) { NC += entry.NC(); }
    return NC;
  };

  /**
   *  @brief Print this MF7/MT4 component
   *
   *  @tparam OutputIterator   an output iterator
   *
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {
    this->alphas_.print( it, MAT, MF, MT );
    for ( auto& entry : this->temperatures_ ) { entry.print( it, MAT, MF, MT ); }
  }
};
