/**
 *  @class
 *  @brief Base class for general covariance representations (LCOMP = 1)
 *
 *  The GeneralCovarianceBase class is used to represent the resonance and
 *  covariance representations (LRU=1 and LRF=1, 2, 3, 4 and 7) for LCOMP = 1
 *  from MF32/MT151.
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
template < typename ShortRangeCovarianceBlock,
           typename RadiusUncertainty,
           typename Derived >
class ENDFTK_PYTHON_EXPORT GeneralCovarianceBase {

  /* fields */

  double spi_;
  double ap_;
  unsigned int nls_;
  double awri_;
  std::optional< RadiusUncertainty > dap_;

  std::vector< ShortRangeCovarianceBlock > short_;
  std::vector< LongRangeCovarianceBlock > long_;

  /* auxiliary functions */

  template< typename Iterator >
  static std::vector< LongRangeCovarianceBlock >
  readSequence( Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT,
                int size ) {

    std::vector< LongRangeCovarianceBlock > sequence;
    sequence.reserve( size );

    while ( size-- ) {

      ListRecord list( begin, end, lineNumber, MAT, MF, MT );

      switch ( list.L2() ) {

        // CovariancePairs
        case -1:
        case 0:
        case 1:
        case 2:
          sequence.emplace_back( section::CovariancePairs( std::move( list ) ) );
          break;

        // SquareMatrix
        case 5:
          sequence.emplace_back( section::SquareMatrix( std::move( list ) ) );
          break;

        // Error
        default:
          Log::error( "Encountered illegal LB value" );
          Log::info( "LB can only be -1,0,1,2,5" );
          Log::info( "LB value: {}", list.L2() );
          Log::info( "Line number: {}", lineNumber - 1 );
          throw std::exception();
      }
    }

    return sequence;
  }

  static void
  verifySize( int NSRS, int NLRS, int LRF ) {

    if ( NSRS < 0 ) {

      Log::error( "Encountered illegal NSRS value" );
      Log::info( "NSRS should be larger than or equal to zero" );
      Log::info( "NSRS value: {}", NSRS );
      throw std::exception();
    }
    if ( LRF != 7 ) {

      if ( NLRS < 0) {

        Log::error( "Encountered illegal NLRS value" );
        Log::info( "NLRS should be larger than or equal to zero" );
        Log::info( "NLRS value: {}", NLRS );
        throw std::exception();
      }
    }
    else {

      if ( NLRS != 0 ) {

        Log::error( "Encountered illegal NLRS value" );
        Log::info( "NLRS should be zero for LRF=7 and LCOMP=1" );
        Log::info( "NLRS value: {}", NLRS );
        throw std::exception();
      }
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  GeneralCovarianceBase( double awri, double spi, double ap,
                         std::optional< RadiusUncertainty >&& dap,
                         unsigned int nls,
                         std::vector< ShortRangeCovarianceBlock >&& cshort,
                         std::vector< LongRangeCovarianceBlock >&& clong ) :
      // no need for a try ... catch: nothing can go wrong here
      spi_( spi ), ap_( ap ), nls_( nls ), awri_( awri ), dap_( dap ),
      short_( std::move( cshort ) ), long_( std::move( clong ) ) {

        verifySize( this->NSRS(), this->NLRS(), this->LRU() );
      }

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  GeneralCovarianceBase( double awri, double spi, double ap,
                         std::optional< RadiusUncertainty >&& dap,
                         unsigned int nls,
                         std::vector< ShortRangeCovarianceBlock >&& cshort,
                         Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT, int NLRS ) :
    // no try ... catch: exceptions will be handled in the derived class
    GeneralCovarianceBase( awri, spi, ap, std::move( dap ), nls, std::move( cshort ),
                           readSequence( it, end, lineNumber, MAT, MF, MT, NLRS ) ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  GeneralCovarianceBase( double awri, double spi, double ap,
                         std::optional< RadiusUncertainty >&& dap,
                         unsigned int nls,
                         Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT, int NSRS, int NLRS ) :
    // no try ... catch: exceptions will be handled in the derived class
    GeneralCovarianceBase( awri, spi, ap, std::move( dap ), nls,
                           njoy::ENDFtk::readSequence< ShortRangeCovarianceBlock >(
                               it, end, lineNumber, MAT, MF, MT, NSRS ),
                           it, end, lineNumber, MAT, MF, MT, NLRS ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  GeneralCovarianceBase( double spi, double ap,
                         std::optional< RadiusUncertainty >&& dap,
                         unsigned int nls,
                         ControlRecord&& cont,
                         Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) :
    // no try ... catch: exceptions will be handled in the derived class
    GeneralCovarianceBase( cont.C1(), spi, ap, std::move( dap ), nls,
                           it, end, lineNumber, MAT, MF, MT,
                           cont.N1(), cont.N2() ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  GeneralCovarianceBase( double spi, double ap,
                         std::optional< RadiusUncertainty >&& dap,
                         unsigned int nls,
                         Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) :
    // no try ... catch: exceptions will be handled in the derived class
    GeneralCovarianceBase( spi, ap, std::move( dap ), nls,
                           ControlRecord( it, end, lineNumber, MAT, MF, MT ),
                           it, end, lineNumber, MAT, MF, MT ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  GeneralCovarianceBase( ControlRecord&& cont,
                         Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) :
    // no try ... catch: exceptions will be handled in the derived class
    GeneralCovarianceBase( cont.C1(), cont.C2(),
                           cont.N2()
                             ? std::make_optional(
                                      Derived::read( it, end, lineNumber,
                                                     MAT, MF, MT ) )
                             : std::nullopt,
                           cont.N1(),
                           it, end, lineNumber, MAT, MF, MT ) {}

protected:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  GeneralCovarianceBase() = default;
  #endif

  /**
   *  @brief Constructor with scattering radius uncertainty
   *
   *  @param[in] awri      the atomic mass ratio
   *  @param[in] spi       the target spin value
   *  @param[in] ap        the scattering radius
   *  @param[in] dap       the scattering radius uncertainty data
   *  @param[in] nls       the number of l values
   *  @param[in] cshort    the short range covariance blocks
   *  @param[in] clong     the long range covariance blocks
   */
  GeneralCovarianceBase( double awri, double spi, double ap,
                         RadiusUncertainty&& dap,
                         unsigned int nls,
                         std::vector< ShortRangeCovarianceBlock >&& cshort,
                         std::vector< LongRangeCovarianceBlock >&& clong ) :
    // no need for a try ... catch: nothing can go wrong here
    GeneralCovarianceBase( awri, spi, ap, std::make_optional( dap ), nls,
                           std::move( cshort ), std::move( clong ) ) {}

  /**
   *  @brief Constructor without scattering radius uncertainty
   *
   *  @param[in] awri      the atomic mass ratio
   *  @param[in] spi       the target spin value
   *  @param[in] ap        the scattering radius
   *  @param[in] nls       the number of l values
   *  @param[in] cshort    the short range covariance blocks
   *  @param[in] clong     the long range covariance blocks
   */
  GeneralCovarianceBase( double awri, double spi, double ap, unsigned int nls,
                         std::vector< ShortRangeCovarianceBlock >&& cshort,
                         std::vector< LongRangeCovarianceBlock >&& clong ) :
    // no need for a try ... catch: nothing can go wrong here
    GeneralCovarianceBase( awri, spi, ap, std::nullopt, nls,
                           std::move( cshort ), std::move( clong ) ) {}

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
   GeneralCovarianceBase( Iterator& it, const Iterator& end, long& lineNumber,
                          int MAT, int MF, int MT ) :
     // no try ... catch: exceptions will be handled in the derived class
     GeneralCovarianceBase(
       ControlRecord( it, end, lineNumber, MAT, MF, MT ),
       it, end, lineNumber, MAT, MF, MT ) {}

public:

  /* get methods */

  /**
   *  @brief Return the covariance representation type
   */
  static constexpr int LCOMP() { return 1; }

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
  static constexpr bool LFW() { return false; }

  /**
  *  @brief Return the average fission flag
  */
  constexpr bool averageFissionWidthFlag() const {

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
   *  @brief Return the number of l values for which resonance parameters are
   *         given
   */
  unsigned int NLS() const { return this->nls_; }

  /**
   *  @brief Return the number of l values for which resonance parameters are
   *         given
   */
  unsigned int numberLValues() const { return this->NLS(); }

  /**
   *  @brief Return the scattering radius uncertainty
   */
  const std::optional< RadiusUncertainty >& DAP() const { return this->dap_; }

  /**
   *  @brief Return the scattering radius uncertainty
   */
  const std::optional< RadiusUncertainty >& scatteringRadiusUncertainty() const {

    return this->DAP();
  }

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double AWRI() const { return this->awri_; }

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double atomicWeightRatio() const { return this->AWRI(); }

  /**
   *  @brief Return the number of short range covariance blocks
   */
  int NSRS() const { return this->short_.size(); }

  /**
   *  @brief Return the number of short range covariance blocks
   */
  int numberShortRangeBlocks() const { return this->NSRS(); }

  /**
   *  @brief Return the number of long range covariance blocks
   */
  int NLRS() const { return this->long_.size(); }

  /**
   *  @brief Return the number of short range covariance blocks
   */
  int numberLongRangeBlocks() const { return this->NLRS(); }

  /**
   *  @brief Return the scattering radius uncertainty flag
   */
  bool ISR() const { return bool( this->dap_ ); }

  /**
   *  @brief Return the angular distribution flag
   */
  bool scatteringRadiusUncertaintyFlag() const { return this->ISR(); }

  /**
   *  @brief Return the short range resonance covariance blocks
   */
  auto shortRangeBlocks() const {

    using namespace njoy::tools;
    return std20::views::all( this->short_ );
  }

  /**
   *  @brief Return the long range resonance covariance blocks
   */
  auto longRangeBlocks() const {

    using namespace njoy::tools;
    return std20::views::all( this->long_ );
  }

  /**
   *  @brief Return the number of lines in this MF32 MT151 component
   */
  long NC() const {

    long NC = 2;
    if ( this->ISR() ) { NC += Derived::NC( this->dap_.value() ); }
    for ( const auto& cshort : this->short_ ) {

      NC += Derived::NC( cshort );
    }
    for ( const auto& clong : this->long_ ) {

      NC += std::visit( [] ( const auto& value ) { return value.NC(); }, clong );
    }
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

      Derived::print( this->dap_.value(), it, MAT, MF, MT );
    }
    ControlRecord( this->AWRI(), 0., 0, 0,
                   this->NSRS(), this->NLRS() ).print( it, MAT, MF, MT );
    for ( const auto& cshort : this->short_ ) {

      Derived::print( cshort, it, MAT, MF, MT );
    }
    for ( const auto& clong : this->long_ ) {

      std::visit( [&] ( const auto& v ) -> void
                      { return v.print( it, MAT, MF, MT ); },
                  clong );
    }
  }
};
