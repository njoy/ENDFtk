/**
 *  @class
 *  @brief General R-matrix limited resonance parameter covariances
 *
 *  See ENDF102, section 32.2.2
 */
class ENDFTK_PYTHON_EXPORT GeneralRMatrixLimited :
  protected GeneralCovarianceBase<
                ShortRangeRMatrixLimitedBlock,
                ReichMooreScatteringRadiusUncertainties,
                GeneralRMatrixLimited > {

  friend GeneralCovarianceBase<
             ShortRangeRMatrixLimitedBlock,
             ReichMooreScatteringRadiusUncertainties,
             GeneralRMatrixLimited >;

protected:

  /* auxiliary functions */

  static long NC( const ReichMooreScatteringRadiusUncertainties& uncertainties ) {

    return uncertainties.NC();
  }

  static long NC( const ShortRangeRMatrixLimitedBlock& block ) {

    return block.NC();
  }

  template< typename OutputIterator >
  static void print( const ReichMooreScatteringRadiusUncertainties& dap,
                     OutputIterator& it, int MAT, int MF, int MT ) {

    dap.print( it, MAT, MF, MT );
  }

  template< typename OutputIterator >
  static void print( const ShortRangeRMatrixLimitedBlock& block, OutputIterator& it,
                     int MAT, int MF, int MT ) {

    block.print( it, MAT, MF, MT );
  }

  template< typename Iterator >
  static ReichMooreScatteringRadiusUncertainties
  read( Iterator&, const Iterator&, long&,
        int, int, int ) {

    // return ReichMooreScatteringRadiusUncertainties( begin, end, lineNumber,
    //                                                 MAT, MF, MT );

    Log::error( "Scattering radius uncertainties in the R-matrix limited representation "
                "are not supported yet." );
    throw std::exception();
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  GeneralRMatrixLimited() = default;
  #endif

  //! @todo enable this when the scattering radius uncertainty format is ready
  // /**
  //  *  @brief Constructor with scattering radius uncertainty
  //  *
  //  *  @param[in] awri      the atomic mass ratio
  //  *  @param[in] cshort    the short range covariance blocks
  //  */
  // GeneralRMatrixLimited( awri,
  //                        ReichMooreScatteringRadiusUncertainties&& dap,
  //                        std::vector< ShortRangeReichMooreBlock >&& cshort ) :
  //   // no need for a try ... catch: nothing can go wrong here
  //   GeneralCovarianceBase( awri, 0., 0., std::move( dap ), 0,
  //                          std::move( cshort ), {} ) {
  //
  //     Log::info( "Encountered error while constructing resonance and covariance "
  //                "parameters in the R-matrix limited representation for the general "
  //                "covariance format (LCOMP = 1)" );
  //     throw;
  //   }

  /**
   *  @brief Constructor without scattering radius uncertainty
   *
   *  @param[in] awri      the atomic mass ratio
   *  @param[in] cshort    the short range covariance blocks
   */
  GeneralRMatrixLimited( double awri,
                         std::vector< ShortRangeRMatrixLimitedBlock >&& cshort )
    try : GeneralCovarianceBase( awri, 0., 0., 0, std::move( cshort ), {} ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance and covariance "
                 "parameters in the R-matrix limited representation for the general "
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
  GeneralRMatrixLimited( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT )
    try : GeneralCovarianceBase( it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance and covariance "
                 "parameters in the R-matrix limited representation for the general "
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
  static constexpr int representation() { return 7; }

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

  using GeneralCovarianceBase::NC;
  using GeneralCovarianceBase::print;
};
