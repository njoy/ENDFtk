/**
 *  @class
 *  @brief Base class for limited Breit-Wigner resonance and covariance
 *         representations (LCOMP = 0)
 *
 *  The LimitedCovarianceBase class is used to represent the SLBW and MLBW
 *  resonance and covariance representations (LRU=1 and LRF=1, 2) for LCOMP=0
 *  from MF32/MT151.
 *
 *  See ENDF102, section 32.2.1 for more information.
 */
template < typename Derived > class LimitedCovarianceBase {

  /* fields */

  double spi_;
  double ap_;
  std::optional< double > dap_;

  std::vector< LimitedBreitWignerLValue > lvalues_;

  /* auxiliary functions */

  static void
  verifySize( int NLS ) {

    if ( NLS < 1 ) {

      Log::error( "Encountered illegal NLS value" );
      Log::info( "NLS should be larger than zero" );
      Log::info( "NLS value: {}", NLS );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  LimitedCovarianceBase( double spi, double ap, std::optional< double >&& dap,
                         std::vector< LimitedBreitWignerLValue >&& lvalues ) :
      // no need for a try ... catch: nothing can go wrong here
      spi_( spi ), ap_( ap ), dap_( dap ),
      lvalues_( std::move( lvalues ) ) {

        verifySize( this->NLS() );
      }

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  LimitedCovarianceBase( double spi, double ap, std::optional< double >&& dap,
                         Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT, int N ) :
    // no try ... catch: exceptions will be handled in the derived class
    LimitedCovarianceBase( spi, ap, std::move( dap ),
                           readSequence< LimitedBreitWignerLValue >(
                               it, end, lineNumber,
                               MAT, MF, MT, N ) ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  LimitedCovarianceBase( ControlRecord&& cont,
                          Iterator& it, const Iterator& end, long& lineNumber,
                          int MAT, int MF, int MT ) :
    // no try ... catch: exceptions will be handled in the derived class
    LimitedCovarianceBase( cont.C1(), cont.C2(),
                           cont.N2()
                             ? std::make_optional( ControlRecord( it, end, lineNumber,
                                                                  MAT, MF, MT ).C2() )
                             : std::nullopt,
                           it, end, lineNumber, MAT, MF, MT, cont.N1() ) {}

protected:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  LimitedCovarianceBase() = default;
  #endif

  /**
   *  @brief Constructor with scattering radius uncertainty
   *
   *  @param[in] spi       the target spin value
   *  @param[in] ap        the scattering radius
   *  @param[in] lvalues   the l values and the resonance parameters
   */
  LimitedCovarianceBase( double spi, double ap, double dap,
                         std::vector< LimitedBreitWignerLValue >&& lvalues ) :
    // no need for a try ... catch: nothing can go wrong here
    LimitedCovarianceBase( spi, ap, std::make_optional( dap ),
                           std::move( lvalues ) ) {}

  /**
   *  @brief Constructor without scattering radius uncertainty
   *
   *  @param[in] spi       the target spin value
   *  @param[in] ap        the scattering radius
   *  @param[in] lvalues   the l values and the resonance parameters
   */
  LimitedCovarianceBase( double spi, double ap,
                         std::vector< LimitedBreitWignerLValue >&& lvalues ) :
    // no need for a try ... catch: nothing can go wrong here
    LimitedCovarianceBase( spi, ap, std::nullopt, std::move( lvalues ) ) {}

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
   LimitedCovarianceBase( Iterator& it, const Iterator& end, long& lineNumber,
                          int MAT, int MF, int MT ) :
     // no try ... catch: exceptions will be handled in the derived class
     LimitedCovarianceBase(
       ControlRecord( it, end, lineNumber, MAT, MF, MT ),
       it, end, lineNumber, MAT, MF, MT ) {}

public:

  /* get methods */

  /**
   *  @brief Return the covariance representation type
   */
  static constexpr int LCOMP() { return 0; }

  /**
   *  @brief Return the covariance representation type
   */
  constexpr int covarianceRepresentation() const { return this->LCOMP(); }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  constexpr int LRU() const {

    return static_cast< const Derived* >( this )->type();
  }

  /**
   *  @brief Return the resonance representation
   */
  constexpr int LRF() const {

    return static_cast< const Derived* >( this )->representation();
  }

  /**
   *  @brief Return the average fission flag
   */
  constexpr bool LFW() const { return false; }

  /**
  *  @brief Return the average fission flag
  */
  constexpr int averageFissionWidthFlag() const {

    return this->LFW();
  }

  /**
   *  @brief Return the target spin
   */
  double SPI() const { return this->spi_; }

  /**
   *  @brief Return the target spin
   */
  double spin() const { return this->SPI(); }

  /**
   *  @brief Return the scattering radius
   */
  double AP() const { return this->ap_; }

  /**
   *  @brief Return the scattering radius
   */
  double scatteringRadius() const { return this->AP(); }

  /**
   *  @brief Return the scattering radius uncertainty
   */
  const std::optional< double >& DAP() const { return this->dap_; }

  /**
   *  @brief Return the scattering radius uncertainty
   */
  const std::optional< double >& scatteringRadiusUncertainty() const {

    return this->DAP();
  }

  /**
   *  @brief Return the number of l values for which resonance parameters are
   *         given
   */
  int NLS() const { return this->lvalues_.size(); }

  /**
   *  @brief Return the number of l values for which resonance parameters are
   *         given
   */
  int numberLValues() const { return this->NLS(); }

  /**
   *  @brief Return the scattering radius uncertainty flag
   */
  bool ISR() const { return bool( this->dap_ ); }

  /**
   *  @brief Return the angular distribution flag
   */
  bool scatteringRadiusUncertaintyFlag() const { return this->ISR(); }

  /**
   *  @brief Return the l values and its resonance parameters
   */
  auto lValues() const {

    using namespace njoy::tools;
    return this->lvalues_ | std20::views::all;
  }

  /**
   *  @brief Return the number of lines in this MF32 MT151 component
   */
  long NC() const {

    long NC = this->ISR() ? 2 : 1;
    for ( const auto& lvalue : this->lvalues_ ) { NC += lvalue.NC(); }
    return NC;
  };

  /**
   *  @brief Print this MF32 MT151 component
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

    ControlRecord( this->SPI(), this->AP(),
                   0, this->LCOMP(),
                   this->NLS(), this->ISR() ).print( it, MAT, MF, MT );
    if ( this->ISR() ) {

      ControlRecord( 0., this->DAP().value(), 0, 0, 0, 0 ).print( it, MAT, MF, MT );
    }
    for ( const auto& lvalue : this->lvalues_ ) {

      lvalue.print( it, MAT, MF, MT );
    }
  }
};
