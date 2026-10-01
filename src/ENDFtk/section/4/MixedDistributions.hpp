/**
 *  @class
 *  @brief The angular distributions are mixed (Legendre coefficients and
 *         tabulated distributions)
 *
 *  The MixedDistributions class is used to represent the case in which
 *  the angular distributions are are given as a region of Legendre
 *  distributions followed by a region of tabulated ditributions.
 *
 *  See ENDF102, section 4.2.3 for more information.
 */
class ENDFTK_PYTHON_EXPORT MixedDistributions {

  /* fields */

  LegendreDistributions legendre_;
  TabulatedDistributions tabulated_;

  /* workaround for the removal of range-v3 */

  // concat is not available in std20 or std23 so we generate the arrays
  // at construction time
  std::vector< long > interpolants_;
  std::vector< long > boundaries_;
  std::vector< double > energies_;
  std::vector< Variant > distributions_;

  void generateArrays() {

    this->interpolants_.clear();
    this->boundaries_.clear();
    this->energies_.clear();
    this->distributions_.clear();

    // interpolants
    this->interpolants_.insert( this->interpolants_.end(),
                                this->legendre().INT().begin(), this->legendre().INT().end() );
    this->interpolants_.insert( this->interpolants_.end(),
                                this->tabulated().INT().begin(), this->tabulated().INT().end() );

    // boundaries
    auto offset = this->legendre().NBT().back();
    this->boundaries_.insert( this->boundaries_.end(),
                              this->legendre().NBT().begin(), this->legendre().NBT().end() );
    std::transform( this->tabulated().NBT().begin(), this->tabulated().NBT().end(),
                    std::back_inserter( this->boundaries_ ),
                    [offset] ( auto&& value ) { return offset + value; } );

    // energies
    this->energies_.insert( this->energies_.end(),
                            this->legendre().incidentEnergies().begin(),
                            this->legendre().incidentEnergies().end() );
    this->energies_.insert( this->energies_.end(),
                            this->tabulated().incidentEnergies().begin(),
                            this->tabulated().incidentEnergies().end() );

    // distributions
    std::transform( this->legendre().angularDistributions().begin(),
                    this->legendre().angularDistributions().end(),
                    std::back_inserter( this->distributions_ ),
                    [] ( auto&& element ) -> Variant { return std::cref( element ); } );
    std::transform( this->tabulated().angularDistributions().begin(),
                    this->tabulated().angularDistributions().end(),
                    std::back_inserter( this->distributions_ ),
                    [] ( auto&& element ) -> Variant { return std::cref( element ); } );
  }

  /* auxiliary functions */

  static void
  verifyBoundary( double left, double right ) {

    if ( left != right ) {

      Log::error( "The upper energy limit for the Legendre distributions "
      	          "does not line up with the lower boundary for the "
      	          "tabulated distributions" );
      Log::info( "Expected initial energy equal to {}", left );
      Log::info( "Found {}", right );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  MixedDistributions( LegendreDistributions&& legendre,
                      Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT ) :
    MixedDistributions( std::move( legendre ),
                        TabulatedDistributions( begin, end, lineNumber,
                                                MAT, MF, MT ) ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] legendre    the legendre distributions
   *  @param[in] tabulated   the tabulated distributions
   */
  MixedDistributions( LegendreDistributions&& legendre,
                      TabulatedDistributions&& tabulated ) :
    legendre_( std::move( legendre ) ), tabulated_( std::move( tabulated ) ) {

      verifyBoundary(
        this->legendre_.angularDistributions().back().incidentEnergy(),
        this->tabulated_.angularDistributions().front().incidentEnergy() );
      this->generateArrays();
    }

  MixedDistributions( const MixedDistributions& base ) :
    legendre_( base.legendre_ ), tabulated_( base.tabulated_ ) {

    this->generateArrays();
  }

  MixedDistributions( MixedDistributions&& base ) :
    legendre_( std::move( base.legendre_ ) ), tabulated_( std::move( base.tabulated_ ) ) {

    this->generateArrays();
  }

  MixedDistributions& operator=( const MixedDistributions& base ) {

    if ( this != &base ) {

      this->legendre_ = base.legendre_;
      this->tabulated_ = base.tabulated_;
      this->generateArrays();
    }
    return *this;
  }

  MixedDistributions& operator=( MixedDistributions&& base ) {

    if ( this != &base ) {

      this->legendre_ = std::move( base.legendre_ );
      this->tabulated_ = std::move( base.tabulated_ );
      this->generateArrays();
    }
    return *this;
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
  MixedDistributions( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT )
    try : MixedDistributions( LegendreDistributions( begin, end, lineNumber,
                                                     MAT, MF, MT ),
                              begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( const std::exception& e ) {

      Log::info( "Error encountered while constructing a mixed "
                 "angular distribution" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  static constexpr bool LI() { return false; }

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  bool isotropicDistributions() const { return this->LI(); }

  /**
   *  @brief Return the angular distribution law
   */
  static constexpr int LTT() { return 3; }

  /**
   *  @brief Return the angular distribution law
   */
  int LAW() const { return this->LTT(); }

  /**
   *  @brief Return the Legendre distributions
   */
  const LegendreDistributions& legendre() const { return this->legendre_; }

  /**
   *  @brief Return the tabulated distributions
   */
  const TabulatedDistributions& tabulated() const { return this->tabulated_; }

  /**
   *  @brief Return the number of interpolation regions
   */
  long NR() const {

    return this->legendre().NR() + this->tabulated().NR();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of energy points for which angular distributions
   *         are available.
   */
  long NE() const {

    return this->legendre().NE() + this->tabulated().NE();
  }

  /**
   *  @brief Return the number of energy points for which angular distributions
   *         are available.
   */
  long numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the boundaries of the interpolation ranges
   *
   *         The intersection point is considered as a jump in the incident
   *         energy.
   */
  auto NBT() const {

    using namespace njoy::tools;
    return std20::views::all( this->boundaries_ );
  }

  /**
   *  @brief Return the boundaries of the interpolation ranges
   *
   *         The intersection point is considered as a jump in the incident
   *         energy.
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the interpolants of the interpolation ranges
   */
  auto INT() const {

    using namespace njoy::tools;
    return std20::views::all( this->interpolants_ );
  }

  /**
   *  @brief Return the interpolants of the interpolation ranges
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the incident energy values
   */
  auto incidentEnergies() const {

    using namespace njoy::tools;
    return std20::views::all( this->energies_ );
  }

  /**
   *  @brief Return the angular distributions (one for each incident energy)
   *
   *  This function returns the underlying angular distributions as a variant
   *  of reference wrappers. See the MixedDistributions unit test for more
   *  information on how to use this.
   */
  auto angularDistributions() const {

    using namespace njoy::tools;
    return std20::views::all( this->distributions_ );
  }

  /**
   *  @brief Return the number of lines for this ENDF component
   */
  long NC() const { return this->legendre_.NC() +
  	                       this->tabulated_.NC(); }

  /** 
   *  @brief Print this MF4 component
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

    this->legendre_.print( it, MAT, MF, MT );
    this->tabulated_.print( it, MAT, MF, MT );
  } 
};
