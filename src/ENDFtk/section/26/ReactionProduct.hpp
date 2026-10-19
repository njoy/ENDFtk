/**
 *  @class
 *  @brief A reaction product with multiplicity and distribution data
 *
 *  The ReactionProduct class is used to represent a reaction product in
 *  an ENDF MF26 section with an associated multiplicity and distribution
 *  (multiple options are available).
 *
 *  See ENDF102, section 26.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ReactionProduct {

  /* fields */

  Multiplicity multiplicity_;
  Distribution law_;

  /* auxiliary functions */

  // taken from MF6

  static void
  verifyLAW( int multiplicityLAW, int distributionLaw ) {

    if ( multiplicityLAW != distributionLaw ) {
      Log::error( "Inconsistent LAW between multiplicity and distribution data" );
      Log::info( "Multiplicity LAW: {}", multiplicityLAW );
      Log::info( "Distribution LAW: {}", distributionLaw );
      throw std::exception();
    }
  }

  template< typename Iterator >
  static Distribution
  readDistribution( Iterator& begin,
                    const Iterator& end,
                    long& lineNumber,
                    int MAT,
                    int MF,
                    int MT,
                    int LAW,
                    long lineLaw ) {
    switch ( LAW ) {
      case   1 : return ContinuumEnergyAngle(
                          begin, end, lineNumber, MAT, MF, MT );
      case   2 : return DiscreteTwoBodyScattering(
                          begin, end, lineNumber, MAT, MF, MT );
      case   8 : return EnergyTransfer( begin, end, lineNumber, MAT, MF, MT );
      default : {
        Log::error( "Encountered illegal LAW value" );
        Log::info( "LAW is equal to 1, 2 or 8" );
        Log::info( "LAW value: {}", LAW );
        Log::info( "Line number: {}", lineLaw - 1 );
        throw std::exception();
      }
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  template< typename Iterator >
  ReactionProduct( Multiplicity&& multiplicity,
                   Iterator& begin, const Iterator& end,
                   long& lineNumber, int MAT, int MF, int MT ) :
    ReactionProduct(
      std::move( multiplicity ),
      readDistribution( begin, end, lineNumber, MAT, MF, MT,
                        multiplicity.LAW(),
                        lineNumber - multiplicity.NC() + 1 ) ) {}

public:

  /* constructor */

  // taken from MF6

  /**
   *  @brief Constructor (one total and multiple partials)
   *
   *  @param[in] multiplicity    the multiplicity
   *  @param[in] distribution    the distribution
   */
  ReactionProduct( Multiplicity&& multiplicity,
                   Distribution&& distribution ) :
    multiplicity_( multiplicity ), law_( distribution ) {

    verifyLAW( this->multiplicity_.LAW(),
               std::visit( [] ( const auto& v ) -> int { return v.LAW(); },
                           this->law_ ) );
  }

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] begin        the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   *  @param[in] NK           the number of partials
   */
  template< typename Iterator >
  ReactionProduct( Iterator& begin, const Iterator& end,
                   long& lineNumber, int MAT, int MF, int MT ) :
    ReactionProduct(
        Multiplicity( begin, end, lineNumber, MAT, MF, MT ),
        begin, end, lineNumber, MAT, MF, MT ) {}

  /* methods */

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  int ZAP() const { return this->multiplicity_.ZAP(); }

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  int productIdentifier() const { return this->ZAP(); }

  /**
   *  @brief Return the atomic weight ratio of the projectile
   */
  double AWI() const { return this->multiplicity_.AWI(); }

  /**
   *  @brief Return the atomic weight ratio of the projectile
   */
  double projectileWeightRatio() const { return this->AWI(); }

  /**
   *  @brief Return the distribution type (the LAW flag)
   */
  int LAW() const { return this->multiplicity_.LAW(); }

  /**
   *  @brief Return the multiplicity
   */
  const Multiplicity& multiplicity() const { return this->multiplicity_; }

  /**
   *  @brief Return the distribution
   */
  const Distribution& distribution() const { return this->law_; }

  /**
   *  @brief Return the number of lines in this MF26 component
   */
  long NC() const { return this->multiplicity_.NC()
                             + std::visit( [] ( const auto& v ) -> long
                                              { return v.NC(); },
                                           this->law_ ); }

  // taken from MF6

  /**
   *  @brief Print this component
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
    this->multiplicity_.print( it, MAT, MF, MT );
    std::visit( [&] ( const auto& v ) -> void
                    { v.print( it, MAT, MF, MT ); },
                this->law_ );
  }
};
