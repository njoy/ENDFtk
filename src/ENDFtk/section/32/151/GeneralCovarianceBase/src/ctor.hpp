private:

/**
 *  @brief Private constructor
 */
GeneralCovarianceBase( double spi, double ap,
                       std::optional< RadiusUncertainty >&& dap,
                       unsigned int nls,
                       std::vector< ShortRangeCovarianceBlock >&& cshort,
                       std::vector< LongRangeCovarianceBlock >&& clong ) :
    // no need for a try ... catch: nothing can go wrong here
    spi_( spi ), ap_( ap ), nls_( nls ), dap_( dap ),
    short_( std::move( cshort ) ), long_( std::move( clong ) ) {

      verifySize( this->NSRS(), this->NLRS(), this->LRU() );
    }

public:
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
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] dap       the scattering radius uncertainty data
 *  @param[in] nls       the number of l values
 *  @param[in] cshort    the short range covariance blocks
 *  @param[in] clong     the long range covariance blocks
 */
GeneralCovarianceBase( double spi, double ap, RadiusUncertainty&& dap,
                       unsigned int nls,
                       std::vector< ShortRangeCovarianceBlock >&& cshort,
                       std::vector< LongRangeCovarianceBlock >&& clong ) :
  // no need for a try ... catch: nothing can go wrong here
  GeneralCovarianceBase( spi, ap, std::make_optional( dap ), nls,
                         std::move( cshort ), std::move( clong ) ) {}

/**
 *  @brief Constructor without scattering radius uncertainty
 *
 *  @param[in] spi       the target spin value
 *  @param[in] ap        the scattering radius
 *  @param[in] nls       the number of l values
 *  @param[in] cshort    the short range covariance blocks
 *  @param[in] clong     the long range covariance blocks
 */
GeneralCovarianceBase( double spi, double ap, unsigned int nls,
                       std::vector< ShortRangeCovarianceBlock >&& cshort,
                       std::vector< LongRangeCovarianceBlock >&& clong ) :
  // no need for a try ... catch: nothing can go wrong here
  GeneralCovarianceBase( spi, ap, std::nullopt, nls,
                         std::move( cshort ), std::move( clong ) ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
GeneralCovarianceBase( double spi, double ap,
                       std::optional< RadiusUncertainty >&& dap,
                       unsigned int nls,
                       std::vector< ShortRangeCovarianceBlock >&& cshort,
                       Iterator& it, const Iterator& end, long& lineNumber,
                       int MAT, int MF, int MT, int NLRS ) :
  // no try ... catch: exceptions will be handled in the derived class
  GeneralCovarianceBase( spi, ap, std::move( dap ), nls, std::move( cshort ),
                         readSequence( it, end, lineNumber, MAT, MF, MT, NLRS ) ) {}

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
GeneralCovarianceBase( double spi, double ap,
                       std::optional< RadiusUncertainty >&& dap,
                       unsigned int nls,
                       Iterator& it, const Iterator& end, long& lineNumber,
                       int MAT, int MF, int MT, int NSRS, int NLRS ) :
  // no try ... catch: exceptions will be handled in the derived class
  GeneralCovarianceBase( spi, ap, std::move( dap ), nls,
                         njoy::ENDFtk::readSequence< ShortRangeCovarianceBlock >(
                             it, end, lineNumber, MAT, MF, MT, NSRS ),
                         it, end, lineNumber, MAT, MF, MT, NLRS ) {}

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
                         it, end, lineNumber, MAT, MF, MT,
                         cont.N1(), cont.N2() ) {}

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
 GeneralCovarianceBase( Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT ) :
   // no try ... catch: exceptions will be handled in the derived class
   GeneralCovarianceBase(
     ControlRecord( it, end, lineNumber, MAT, MF, MT ),
     it, end, lineNumber, MAT, MF, MT ) {}
