/**
 *  @class
 *  @brief Coherent elastic scattering law
 *
 *  The CoherentElastic class is used to represent the coherent elastic
 *  scattering law of MF7/MT2.
 *
 *  The S(E) functions are given as tabulated S(E) for a set of temperature
 *  values.
 *
 *  See ENDF102, section 7.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT CoherentElastic {

  /* members */

  TabulationRecord principal_;
  std::vector< ListRecord > temperatures_;

  /* auxiliary functions */

  static std::vector< ListRecord >
  generateTemperatures( std::vector< double >&& temperatures,
                        std::vector< long >&& li,
                        std::vector< std::vector< double > >&& s ) {

    std::vector< ListRecord > sequence;

    unsigned int size = temperatures.size() - 1;
    if ( size + 1 != s.size() ) {

      Log::error( "Inconsistent number of temperatures and S(E,T) functions" );
      Log::info( "The number of temperatures must be equal to the number of "
                 "S(E,T) functions" );
      Log::info( "Number of temperatures: {}", size + 1 );
      Log::info( "Number of S(E,T) functions: {}", s.size() );
      throw std::exception();
    }

    sequence.reserve( size );
    unsigned int i = 0;
    while( i++ < size ) {

      sequence.emplace_back( ListRecord( temperatures[i], 0, li[i-1], 0, 0,
                                         std::move( s[i] ) ) );
    }

    return sequence;
  }

  template< typename Array >
  static void
  verifyTemperatures( int NP, const Array& temperatures ) {

    auto compare = [NP] ( const auto& entry )
                        { return entry.NPL() == NP; };

    auto iter = std::find_if_not( temperatures.begin(), temperatures.end(), compare );

    if ( iter != temperatures.end() ) {

      using namespace njoy::tools;
      Log::error( "All S(E,T) functions must have the same size" );
      Log::info( "Expected NP={} for the temperature with index={}", NP,
                 std20::ranges::distance( temperatures.begin(), iter ) );
      throw std::exception();
    }
  }

  /* workaround for the removal of range-v3 */

  // range-v3 allowed for concatenation of different ranges but our new capability
  // does not. we therefore generate these arrays at construction time
  using Array = decltype( principal_.y() );
  std::vector< Array > s_;
  std::vector< double > t_;

  void  generateSandT() {

    this->s_.clear();
    this->t_.clear();

    this->s_.reserve( this->numberTemperatures() );
    this->t_.reserve( this->numberTemperatures() );

    this->s_.emplace_back( this->principal_.y() );
    this->t_.push_back( this->principal_.C1() );
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
  CoherentElastic( TabulationRecord&& principal,
                   std::vector< ListRecord >&& temperatures ) :
    principal_( std::move( principal ) ),
    temperatures_( std::move( temperatures ) ) {

    this->generateSandT();
    verifyTemperatures( this->NP(), this->temperatures_ );
  }

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  CoherentElastic( TabulationRecord&& principal,
                   Iterator& begin,
                   const Iterator& end,
                   long& lineNumber,
                   int MAT,
                   int MF,
                   int MT ) :
    CoherentElastic( std::move( principal ),
                     readSequence< ListRecord >(
                         begin, end, lineNumber,
                         MAT, MF, MT, principal.L1() ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  CoherentElastic() = default;
  #endif

  CoherentElastic( const CoherentElastic& f ) :
    principal_( f.principal_ ), temperatures_( f.temperatures_ ) {

    this->generateSandT();
  }

  CoherentElastic( CoherentElastic&& f ) :
    principal_( std::move( f.principal_ ) ), temperatures_( std::move( f.temperatures_ ) ) {

    this->generateSandT();
  }

  /**
   *  @brief Constructor (multiple temperatures)
   *
   *  The size of the various arrays is checked for consistency where appropriate.
   *
   *  @param[in] boundaries     the interpolation range boundaries for S(E)
   *  @param[in] interpolants   the interpolation types for each range
   *  @param[in] temperatures   the temperatures (NT values)
   *  @param[in] li             the temperature interpolation flags (NT-1 values)
   *  @param[in] energies       the energy values (NP values)
   *  @param[in] s              the thermal scattering values (NT arrays of NP
   *                            values)
   */
  CoherentElastic( std::vector< long >&& boundaries,
                   std::vector< long >&& interpolants,
                   std::vector< double >&& temperatures,
                   std::vector< long >&& li,
                   std::vector< double >&& energies,
                   std::vector< std::vector< double > >&& s )
    try : CoherentElastic( TabulationRecord( temperatures[0], 0,
                                             temperatures.size() - 1, 0,
                                             std::move( boundaries ),
                                             std::move( interpolants ),
                                             std::move( energies ),
                                             std::move( s[0] ) ),
                           generateTemperatures( std::move( temperatures ),
                                                 std::move( li ),
                                                 std::move( s ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing coherent elastic "
                 "scattering data" );
      throw;
    }

  /**
   *  @brief Constructor (single temperature)
   *
   *  The size of the various arrays is checked for consistency where appropriate.
   *
   *  @param[in] temperature    the temperature
   *  @param[in] boundaries     the interpolation range boundaries for S(E)
   *  @param[in] interpolants   the interpolation types for each range
   *  @param[in] energies       the energy values (NP values)
   *  @param[in] s              the thermal scattering values (NP values)
   */
  CoherentElastic( double temperature,
                   std::vector< long >&& boundaries,
                   std::vector< long >&& interpolants,
                   std::vector< double >&& energies,
                   std::vector< double >&& s )
    try : CoherentElastic( TabulationRecord( temperature, 0, 0, 0,
                                             std::move( boundaries ),
                                             std::move( interpolants ),
                                             std::move( energies ),
                                             std::move( s ) ), {} ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing coherent elastic "
                 "scattering data" );
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
  CoherentElastic( Iterator& begin,
                   const Iterator& end,
                   long& lineNumber,
                   int MAT,
                   int MF,
                   int MT )
    try : CoherentElastic( TabulationRecord( begin, end, lineNumber,
                                             MAT, MF, MT ),
                           begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading coherent elastic "
                 "scattering data" );
      throw;
    }

  CoherentElastic& operator=( const CoherentElastic& base ) {

    if ( this != &base ) {

      this->principal_ = base.principal_;
      this->temperatures_ = base.temperatures_;
      this->generateSandT();
    }
    return *this;
  }

  CoherentElastic& operator=( CoherentElastic&& base ) {

    if ( this != &base ) {

      this->principal_ = std::move( base.principal_ );
      this->temperatures_ = std::move( base.temperatures_ );
      this->generateSandT();
    }
    return *this;
  }

  /* get methods */

  /**
   *  @brief Return the LTHR flag for coherent elastic scattering
   */
  static constexpr int LTHR() { return 1; }

  /**
   *  @brief Return the LTHR flag for coherent elastic scattering
   */
  int elasticScatteringType() const { return this->LTHR(); }

  /**
   *  @brief Return the LT flag indicating the temperature dependence (equal to
   *         NT - 1)
   */
  int LT() const { return this->principal_.L1(); }

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
   *  @brief Return the number of interpolation ranges on the energy grid
   */
  long NR() const { return this->principal_.NR(); }

  /**
   *  @brief Return the number of interpolation ranges on the energy grid
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of Bragg edges, equal to the number of energy
   *         values
   */
  long NP() const { return this->principal_.NP(); }

  /**
   *  @brief Return the number of Bragg edges, equal to the number of energy
   *         values
   */
  long numberPoints() const { return this->NP(); }

  /**
   *  @brief Return the number of Bragg edges, equal to the number of energy
   *         values
   */
  long numberBraggEdges() const { return this->NP(); }

  /**
   *  @brief Return interpolation type for each range on the energy grid
   */
  auto INT() const { return this->principal_.INT(); }

  /**
   *  @brief Return interpolation type for each range on the energy grid
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return interpolation boundaries for the energy grid
   */
  auto NBT() const { return this->principal_.NBT(); }

  /**
   *  @brief Return interpolation boundaries for the energy grid
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return all temperatures for which thermal scattering law data is
   *         given
   */
  auto T() const {

    using namespace njoy::tools;
    return std20::views::all( this->t_ );
  }

  /**
   *  @brief Return all temperatures for which thermal scattering law data is
   *         given
   */
  auto temperatures() const { return this->T(); }

  /**
   *  @brief Return the energy grid
   */
  auto E() const { return this->principal_.x(); }

  /**
   *  @brief Return the energy grid
   */
  auto energies() const { return this->E(); }

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
    return std20::views::all( this->s_ );
  }

  /**
   *  @brief Return the thermal scattering law values as an array, one for each
   *         temperature
   */
  auto thermalScatteringValues() const { return this->S(); }

  /**
   *  @brief Return the number of lines in this MF7/MT2 component
   */
  long NC() const {

    long NC = this->principal_.NC();
    for ( const auto& entry : this->temperatures_ ) { NC += entry.NC(); }
    return NC;
  };

  /**
   *  @brief Print this MF7/MT2 component
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

    this->principal_.print( it, MAT, MF, MT );
    for ( auto& entry : this->temperatures_ ) { entry.print( it, MAT, MF, MT ); }
  }
};
