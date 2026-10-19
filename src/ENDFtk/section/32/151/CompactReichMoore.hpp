/**
 *  @class
 *  @brief Compact Reich-Moore resonance parameter covariances
 *
 *  See ENDF102, section 32.2.3.2
 */
class ENDFTK_PYTHON_EXPORT CompactReichMoore :
  protected CompactCovarianceBase<
                CompactReichMooreUncertainties,
                ReichMooreScatteringRadiusUncertainties,
                CompactReichMoore > {

  friend CompactCovarianceBase<
             CompactReichMooreUncertainties,
             ReichMooreScatteringRadiusUncertainties,
             CompactReichMoore >;

protected:

  /* auxiliary functions */

  static long NC( const ReichMooreScatteringRadiusUncertainties& uncertainties ) {

    return uncertainties.NC();
  }

  template< typename OutputIterator >
  static void print( const ReichMooreScatteringRadiusUncertainties& dap,
                     OutputIterator& it, int MAT, int MF, int MT ) {

    dap.print( it, MAT, MF, MT );
  }

  template< typename Iterator >
  static ReichMooreScatteringRadiusUncertainties
  read( Iterator& begin, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT ) {

    return ReichMooreScatteringRadiusUncertainties( begin, end, lineNumber,
                                                    MAT, MF, MT );
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  CompactReichMoore() = default;
  #endif

  /**
   *  @brief Constructor with scattering radius uncertainty
   *
   *  @param[in] spi           the target spin value
   *  @param[in] ap            the scattering radius
   *  @param[in] lad           the angular distribution flag
   *  @param[in] dap           the scattering radius uncertainty data
   *  @param[in] parameters    the resonance parameters and uncertainties
   *  @param[in] matrix        the correlation matrix
   */
  CompactReichMoore( double spi, double ap, bool lad,
                     ReichMooreScatteringRadiusUncertainties&& dap,
                     CompactReichMooreUncertainties&& parameters,
                     CompactCorrelationMatrix&& matrix )
    // no need for a try ... catch: nothing can go wrong here
    try : CompactCovarianceBase( spi, ap, std::move( dap ),
                           static_cast< long >( lad ), 0.,
                           std::move( parameters ), std::move( matrix ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance and covariance "
                 "parameters in the Reich-Moore representation for the compact "
                 "covariance format (LCOMP = 2)" );
      throw;
    }

  /**
   *  @brief Constructor without scattering radius uncertainty
   *
   *  @param[in] spi           the target spin value
   *  @param[in] ap            the scattering radius
   *  @param[in] lad           the angular distribution flag
   *  @param[in] dap           the scattering radius uncertainty data
   *  @param[in] parameters    the resonance parameters and uncertainties
   *  @param[in] matrix        the correlation matrix
   */
  CompactReichMoore( double spi, double ap, bool lad,
                     CompactReichMooreUncertainties&& parameters,
                     CompactCorrelationMatrix&& matrix )
    try : CompactCovarianceBase( spi, ap,
                                 static_cast< long >( lad ), 0,
                                 std::move( parameters ),
                                 std::move( matrix ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance and covariance "
                 "parameters in the Reich-Moore representation for the compact "
                 "covariance format (LCOMP = 2)" );
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
  CompactReichMoore( Iterator& it, const Iterator& end, long& lineNumber,
                     int MAT, int MF, int MT )
    try : CompactCovarianceBase( it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance and covariance "
                 "parameters in the Reich-Moore representation for the compact "
                 "covariance format (LCOMP = 2)" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 3; }

  /**
   *  @brief Return the angular distribution flag
   */
  bool LAD() const { return CompactCovarianceBase::L1(); }

  /**
   *  @brief Return the angular distribution flag
   */
  bool angularDistributionsFlag() const { return this->LAD(); }

  using CompactCovarianceBase::LRU;
  using CompactCovarianceBase::LRF;
  using CompactCovarianceBase::LFW;
  using CompactCovarianceBase::averageFissionWidthFlag;
  using CompactCovarianceBase::LCOMP;
  using CompactCovarianceBase::covarianceRepresentation;

  using CompactCovarianceBase::SPI;
  using CompactCovarianceBase::spin;
  using CompactCovarianceBase::AP;
  using CompactCovarianceBase::scatteringRadius;
  using CompactCovarianceBase::DAP;
  using CompactCovarianceBase::scatteringRadiusUncertainty;
  using CompactCovarianceBase::ISR;
  using CompactCovarianceBase::scatteringRadiusUncertaintyFlag;
  using CompactCovarianceBase::uncertainties;
  using CompactCovarianceBase::correlationMatrix;

  using CompactCovarianceBase::NC;
  using CompactCovarianceBase::print;
};
