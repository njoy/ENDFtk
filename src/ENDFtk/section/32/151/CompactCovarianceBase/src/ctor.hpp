private:

/**
 *  @brief Private constructor
 */
CompactCovarianceBase( double spi, double ap, long l1, long n1,
                       std::optional< RadiusUncertainty >&& dap,
                       ResonanceParameterUncertainties&& uncertainties,
                       CompactCorrelationMatrix&& matrix ) :
    // no need for a try ... catch: nothing can go wrong here
    spi_( spi ), ap_( ap ), l1_( n1 ), n1_( l1 ), dap_( dap ),
    uncertainties_( std::move( uncertainties ) ), matrix_( std::move( matrix ) ) {

//      verifySize( this->NSRS(), this->NLRS(), this->LRU() );
    }

public:
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

private:

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
                                                          MAT, MF, MT ),
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
