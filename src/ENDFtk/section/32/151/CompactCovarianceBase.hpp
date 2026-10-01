/**
 *  @class
 *  @brief Base class for compact covariance representations (LCOMP = 2)
 *
 *  The CompactCovarianceBase class is used to represent the resonance and
 *  covariance representations (LRU=1 and LRF = 1, 2, 3 and 7) for LCOMP = 2
 *  from MF32/MT151.
 *
 *  See ENDF102, section 32.2.3 for more information.
 */
template < typename ResonanceParameterUncertainties,
           typename RadiusUncertainty,
           typename Derived >
class CompactCovarianceBase {

  /* fields */

  double spi_;
  double ap_;
  long l1_;
  long n1_;
  std::optional< RadiusUncertainty > dap_;

  ResonanceParameterUncertainties uncertainties_;
  CompactCorrelationMatrix matrix_;

  /* auxiliary functions */

  /* constructor */

  /**
   *  @brief Private constructor
   */
  CompactCovarianceBase( double spi, double ap, long l1, long n1,
                         std::optional< RadiusUncertainty >&& dap,
                         ResonanceParameterUncertainties&& uncertainties,
                         CompactCorrelationMatrix&& matrix ) :
      // no need for a try ... catch: nothing can go wrong here
      spi_( spi ), ap_( ap ), l1_( l1 ), n1_( n1 ), dap_( dap ),
      uncertainties_( std::move( uncertainties ) ), matrix_( std::move( matrix ) ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  CompactCovarianceBase( double spi, double ap, long l1, long n1,
                         std::optional< RadiusUncertainty >&& dap,
                         ResonanceParameterUncertainties&& uncertainties,
                         Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) :
    // no try ... catch: exceptions will be handled in the derived class
    CompactCovarianceBase( spi, ap, l1, n1, std::move( dap ),
                           std::move( uncertainties ),
                           CompactCorrelationMatrix( it, end, lineNumber,
                                                     MAT, MF, MT ) ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  CompactCovarianceBase( double spi, double ap, long l1, long n1,
                         std::optional< RadiusUncertainty >&& dap,
                         Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) :
    // no try ... catch: exceptions will be handled in the derived class
    CompactCovarianceBase( spi, ap, l1, n1, std::move( dap ),
                           ResonanceParameterUncertainties( it, end, lineNumber,
                                                            MAT, MF, MT, n1 ),
                           it, end, lineNumber, MAT, MF, MT ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  CompactCovarianceBase( ControlRecord&& cont,
                         Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) :
    // no try ... catch: exceptions will be handled in the derived class
    CompactCovarianceBase( cont.C1(), cont.C2(), cont.L1(), cont.N1(),
                           cont.N2()
                             ? std::make_optional(
                                      Derived::read( it, end, lineNumber,
                                                     MAT, MF, MT ) )
                             : std::nullopt,
                           it, end, lineNumber, MAT, MF, MT ) {}


protected:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  CompactCovarianceBase() = default;
  #endif

  /**
   *  @brief Constructor with scattering radius uncertainty
   *
   *  @param[in] spi             the target spin value
   *  @param[in] ap              the scattering radius
   *  @param[in] dap             the scattering radius uncertainty data
   *  @param[in] l1              the L1 value
   *  @param[in] n1              the N1 value
   *  @param[in] uncertainties   the resonance uncertainties and uncertainties
   *  @param[in] matrix          the correlation matrix
   */
  CompactCovarianceBase( double spi, double ap, RadiusUncertainty&& dap,
                         long l1, long n1,
                         ResonanceParameterUncertainties&& uncertainties,
                         CompactCorrelationMatrix&& matrix ) :
    // no need for a try ... catch: nothing can go wrong here
    CompactCovarianceBase( spi, ap, l1, n1, std::make_optional( dap ),
                           std::move( uncertainties ), std::move( matrix ) ) {}

  /**
   *  @brief Constructor without scattering radius uncertainty
   *
   *  @param[in] spi             the target spin value
   *  @param[in] ap              the scattering radius
   *  @param[in] l1              the L1 value
   *  @param[in] n1              the N1 value
   *  @param[in] uncertainties   the resonance uncertainties and uncertainties
   *  @param[in] matrix          the correlation matrix
   */
  CompactCovarianceBase( double spi, double ap, long l1, long n1,
    ResonanceParameterUncertainties&& uncertainties,
    CompactCorrelationMatrix&& matrix ) :
    // no need for a try ... catch: nothing can go wrong here
    CompactCovarianceBase( spi, ap, l1, n1, std::nullopt,
                           std::move( uncertainties ), std::move( matrix ) ) {}

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
   CompactCovarianceBase( Iterator& it, const Iterator& end, long& lineNumber,
                          int MAT, int MF, int MT ) :
     // no try ... catch: exceptions will be handled in the derived class
     CompactCovarianceBase(
       ControlRecord( it, end, lineNumber, MAT, MF, MT ),
       it, end, lineNumber, MAT, MF, MT ) {}

public:

  /* get methods */

  /**
   *  @brief Return the covariance representation type
   */
  static constexpr int LCOMP() { return 2; }

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
   *  @brief Return the value of L1
   */
  long L1() const { return this->l1_; }

  /**
   *  @brief Return the value of N1
   */
  long N1() const { return this->n1_; }

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
   *  @brief Return the scattering radius uncertainty flag
   */
  bool ISR() const { return bool( this->dap_ ); }

  /**
   *  @brief Return the angular distribution flag
   */
  bool scatteringRadiusUncertaintyFlag() const { return this->ISR(); }

  /**
   *  @brief Return the resonance parameter uncertainties
   */
  const ResonanceParameterUncertainties& uncertainties() const {

    return this->uncertainties_;
  }

  /**
   *  @brief Return the correlation matrix
   */
  const CompactCorrelationMatrix& correlationMatrix() const {

    return this->matrix_;
  }

  /**
   *  @brief Return the number of lines in this MF32 MT151 component
   */
  long NC() const {

    long NC = 1;
    if ( this->ISR() ) { NC += Derived::NC( this->dap_.value() ); }
    NC += this->uncertainties_.NC();
    NC += this->matrix_.NC();
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
                   this->L1(), this->LCOMP(),
                   this->N1(), this->ISR() ).print( it, MAT, MF, MT );
    if ( this->ISR() ) {

      Derived::print( this->dap_.value(), it, MAT, MF, MT );
    }
    this->uncertainties_.print( it, MAT, MF, MT );
    this->matrix_.print( it, MAT, MF, MT );
  }
};
