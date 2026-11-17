/**
 *  @class
 *  @brief General Reich-Moore resonance parameter covariances
 *
 *  See ENDF102, section 32.2.2
 */
class ENDFTK_PYTHON_EXPORT GeneralReichMoore :
  protected GeneralCovarianceBase<
                ShortRangeReichMooreBlock,
                ReichMooreScatteringRadiusUncertainties,
                GeneralReichMoore > {

  friend GeneralCovarianceBase<
             ShortRangeReichMooreBlock,
             ReichMooreScatteringRadiusUncertainties,
             GeneralReichMoore >;

protected:

  /* auxiliary functions */

  static long NC( const ReichMooreScatteringRadiusUncertainties& uncertainties ) {

    return uncertainties.NC();
  }

  static long NC( const ShortRangeReichMooreBlock& block ) {

    return block.NC();
  }

  template< typename OutputIterator >
  static void print( const ReichMooreScatteringRadiusUncertainties& dap,
                     OutputIterator& it, int MAT, int MF, int MT ) {

    dap.print( it, MAT, MF, MT );
  }

  template< typename OutputIterator >
  static void print( const ShortRangeReichMooreBlock& block, OutputIterator& it,
                     int MAT, int MF, int MT ) {

    block.print( it, MAT, MF, MT );
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
  GeneralReichMoore() = default;
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
  GeneralReichMoore( double awri, double spi, double ap,
                     ReichMooreScatteringRadiusUncertainties&& dap,
                     unsigned int nls,
                     std::vector< ShortRangeReichMooreBlock >&& cshort,
                     std::vector< LongRangeCovarianceBlock >&& clong )
    try : GeneralCovarianceBase( awri, spi, ap, std::move( dap ), nls,
                                 std::move( cshort ), std::move( clong ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance and covariance "
                 "parameters in the Reich-Moore representation for the general "
                 "covariance format (LCOMP = 1)" );
      throw;
    }

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
  GeneralReichMoore( double awri, double spi, double ap, unsigned int nls,
                     std::vector< ShortRangeReichMooreBlock >&& cshort,
                     std::vector< LongRangeCovarianceBlock >&& clong )
    try : GeneralCovarianceBase( awri, spi, ap, nls,
                                 std::move( cshort ), std::move( clong ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance and covariance "
                 "parameters in the Reich-Moore representation for the general "
                 "covariance format (LCOMP = 1)" );
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
  GeneralReichMoore( Iterator& it, const Iterator& end, long& lineNumber,
                     int MAT, int MF, int MT )
    try : GeneralCovarianceBase( it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance and covariance "
                 "parameters in the Reich-Moore representation for the general "
                 "covariance format (LCOMP = 1)" );
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

  using GeneralCovarianceBase::LRU;
  using GeneralCovarianceBase::LRF;
  using GeneralCovarianceBase::LFW;
  using GeneralCovarianceBase::averageFissionWidthFlag;
  using GeneralCovarianceBase::LCOMP;
  using GeneralCovarianceBase::covarianceRepresentation;

  using GeneralCovarianceBase::AWRI;
  using GeneralCovarianceBase::atomicWeightRatio;
  using GeneralCovarianceBase::SPI;
  using GeneralCovarianceBase::spin;
  using GeneralCovarianceBase::AP;
  using GeneralCovarianceBase::scatteringRadius;
  using GeneralCovarianceBase::NLS;
  using GeneralCovarianceBase::numberLValues;
  using GeneralCovarianceBase::DAP;
  using GeneralCovarianceBase::scatteringRadiusUncertainty;
  using GeneralCovarianceBase::NSRS;
  using GeneralCovarianceBase::numberShortRangeBlocks;
  using GeneralCovarianceBase::NLRS;
  using GeneralCovarianceBase::numberLongRangeBlocks;
  using GeneralCovarianceBase::ISR;
  using GeneralCovarianceBase::scatteringRadiusUncertaintyFlag;
  using GeneralCovarianceBase::shortRangeBlocks;
  using GeneralCovarianceBase::longRangeBlocks;

  using GeneralCovarianceBase::NC;
  using GeneralCovarianceBase::print;
};
