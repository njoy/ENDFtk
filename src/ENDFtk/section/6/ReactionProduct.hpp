/**
 *  @class
 *  @brief A reaction product with multiplicity and distribution data
 *
 *  The ReactionProduct class is used to represent a reaction product in
 *  an ENDF MF6 section with an associated multiplicity and distribution
 *  (multiple options are available).
 *
 *  See ENDF102, section 6.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ReactionProduct {

  /* fields */

  Multiplicity multiplicity_;
  Distribution law_;

  /* auxiliary functions */

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
      case  -4 :
      case  -5 :
      case -14 :
      case -15 : {
        if ( MT != 18 ) {
          Log::error( "Encountered illegal LAW value for non fission reaction" );
          Log::info( "LAW can only be negative for MT=18" );
          Log::info( "MT value: {}", MT );
          Log::info( "Line number: {}", lineLaw - 1 );
          throw std::exception();
        }
        return DefinedElsewhere( LAW );
      }
      case   0 : return Unknown();
      case   1 : return ContinuumEnergyAngle(
                          begin, end, lineNumber, MAT, MF, MT );
      case   2 : return DiscreteTwoBodyScattering(
                          begin, end, lineNumber, MAT, MF, MT );
      case   3 : return IsotropicDiscreteEmission();
      case   4 : return DiscreteTwoBodyRecoils();
      case   5 : return ChargedParticleElasticScattering(
                          begin, end, lineNumber, MAT, MF, MT );
      case   6 : return NBodyPhaseSpace( begin, end, lineNumber, MAT, MF, MT );
      case   7 : return LaboratoryAngleEnergy(
                          begin, end, lineNumber, MAT, MF, MT );
      default : {
        Log::error( "Encountered illegal LAW value" );
        Log::info( "LAW is negative or equal to a value between 0 and 7" );
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
   *  @brief Return the atomic weight ratio of the reaction product
   */
  double AWP() const { return this->multiplicity_.AWP(); }

  /**
   *  @brief Return the atomic weight ratio of the reaction product
   */
  double productWeightRatio() const { return this->AWP(); }

  /**
   *  @brief Return the product modifier flag
   */
  int LIP() const { return this->multiplicity_.LIP(); }

  /**
   *  @brief Return the product modifier flag
   */
  int productModifierFlag() const { return this->LIP(); }

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
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return this->multiplicity_.NC()
                             + std::visit( [] ( const auto& v ) -> long
                                              { return v.NC(); },
                                           this->law_ ); }

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
