/**
 *  @class
 *  @brief A resonance energy range with parameters
 *
 *  The ResonanceRange class is used to represent a resonance range (resolved
 *  or unresolved) from MF2/MT151.
 *
 *  See ENDF102, section 2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT ResonanceRange {

public:

  /* type aliases */

  using OptionalScatteringRadius = std::optional< ScatteringRadius >;

  using ResonanceParameters =
          std::variant<
              // LRU=0
              SpecialCase,
              // LRU=1
              SingleLevelBreitWigner, // LRF = 1
              MultiLevelBreitWigner,  // LRF = 2
              ReichMoore,             // LRF = 3
              RMatrixLimited,         // LRF = 7
              // LRU=2
              UnresolvedEnergyIndependent,            // LRF = 1, LFW = 0
              UnresolvedEnergyDependentFissionWidths, // LRF = 1, LFW = 1
              UnresolvedEnergyDependent >;            // LRF = 1

private:

  /* fields */

  double el_;
  double eh_;
  int naps_;

  ResonanceParameters parameters_;
  OptionalScatteringRadius scattering_radius_;

  /* auxiliary functions */

  static void
  verifyOptions( bool NRO, int NAPS, int LRU, int LRF ) {

    if ( not NRO and ( ( NAPS < 0 ) or ( NAPS > 1 ) ) ) {

      Log::error( "Encountered illegal NAPS value" );
      Log::info( "NAPS is either 0 or 1 when no energy dependent scattering "
                 "radius is given (NRO = 0)" );
      Log::info( "NRO value: {}", int( NRO ) );
      Log::info( "NAPS value: {}", NAPS );
      throw std::exception();
    }

    if ( NRO and ( ( NAPS < 0 ) or ( NAPS > 2 ) ) ) {

      Log::error( "Encountered illegal NAPS value" );
      Log::info( "NAPS is either 0, 1 or 2 when an energy dependent scattering "
                 "radius is given (NRO = 1)" );
      Log::info( "NRO value: {}", int( NRO ) );
      Log::info( "NAPS value: {}", NAPS );
      throw std::exception();
    }

    if ( NRO and ( LRU == 0 ) ) {

      Log::error( "An energy dependent scattering radius is not allowed for "
                  "the scattering radius only special case (LRU = 0, LRF = 0)" );
      Log::info( "NRO value: {}", int( NRO ) );
      throw std::exception();
    }

    if ( NRO and ( LRU == 1 ) and ( LRF == 7 ) ) {

      Log::error( "An energy dependent scattering radius is not allowed for "
                  "a Limited R-matrix resonance range (LRU = 1, LRF = 7)" );
      Log::info( "NRO value: {}", int( NRO ) );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] el                 the lower energy of the resonance region
   *  @param[in] eh                 the upper energy of the resonance region
   *  @param[in] naps               the flag to indicate then on how to calculate
   *                                the scattering radius (0 or 1 if no energy
   *                                dependent scattering radius is given and 0, 1
   *                                or 2 if energy dependent scattering radius is
   *                                given)
   *  @param[in] parameters         the resonance parameters
   *  @param[in] scatteringRadius   An optional energy dependent scattering radius
   */
  ResonanceRange( double el, double eh, int naps,
                  ResonanceParameters&& parameters,
                  std::optional< ScatteringRadius >&& scatteringRadius = std::nullopt )
    try : el_( el ), eh_( eh ), naps_( naps ),
          parameters_( std::move( parameters ) ),
          scattering_radius_( std::move( scatteringRadius ) ) {

      verifyOptions( this->NRO(), this->NAPS(), this->LRU(), this->LRF() );
    }
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a resonance range" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the lower energy boundary of the resonance region
   */
  double EL() const { return this->el_; }

  /**
   *  @brief Return the lower energy boundary of the resonance region
   */
  double lowerEnergy() const { return this->EL(); }

  /**
   *  @brief Return the upper energy boundary of the resonance region
   */
  double EH() const { return this->eh_; }

  /**
   *  @brief Return the upper energy boundary of the resonance region
   */
  double upperEnergy() const { return this->EH(); }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  int LRU() const { return std::visit( [] ( const auto& v ) -> int
                                          { return v.LRU(); },
                                        this->parameters_ ); }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  int type() const { return this->LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  int LRF() const { return std::visit( [] ( const auto& v ) -> int
                                          { return v.LRF(); },
                                        this->parameters_ ); }

  /**
   *  @brief Return the resonance representation
   */
  int representation() const { return this->LRF(); }

  /**
   *  @brief Return the average fission flag
   */
  bool LFW() const { return std::visit( [] ( const auto& v ) -> bool
                                          { return v.LFW(); },
                                        this->parameters_ ); }

  /**
   *  @brief Return the average fission flag
   */
  bool averageFissionWidthFlag() const { return this->LFW(); }

  /**
   *  @brief Return whether the scattering radius is energy dependent or not
   */
  bool NRO() const { return bool( this->scattering_radius_ ); }

  /**
   *  @brief Return whether the scattering radius is energy dependent or not
   */
  bool energyDependentScatteringRadius() const { return this->NRO(); }

  /**
   *  @brief Return scattering radius calculation option flag
   */
  int NAPS() const { return this->naps_; }

  /**
   *  @brief Return scattering radius calculation option flag
   */
  int scatteringRadiusCalculationOption() const { return this->NAPS(); }

  /**
   *  @brief Return optional scattering radius
   */
  const OptionalScatteringRadius& scatteringRadius() const {

    return this->scattering_radius_;
  }

  /**
   *  @brief Return the resonance parameters
   */
  const ResonanceParameters& parameters() const { return this->parameters_; }

  /**
   *  @brief Return the number of lines in this MF2/MT151 component
   */
  long NC() const {

    long NC = 1 + std::visit( [] ( const auto& v ) -> long
                                 { return v.NC(); },
                              this->parameters_ );
    if ( this->NRO() ) { NC += this->scattering_radius_->NC(); }
    return NC;
  }

  /**
   *  @brief Print this MF2/MT151 component
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

    ControlRecord( this->EL(), this->EH(),
                   this->LRU(), this->LRF(),
                   this->NRO(), this->NAPS() ).print( it, MAT, MF, MT );
    if ( this->NRO() ) { this->scattering_radius_->print( it, MAT, MF, MT ); }
    std::visit( [&] ( const auto& v ) -> void
                    { return v.print( it, MAT, MF, MT ); },
                this->parameters_ );
  }
};
