/**
 *  @class
 *  @brief Compact R-matrix limited resonance parameter covariances
 *
 *  See ENDF102, section 32.2.3.2
 */
class ENDFTK_PYTHON_EXPORT CompactRMatrixLimited :
  protected CompactCovarianceBase<
                CompactRMatrixLimitedUncertainties,
                ReichMooreScatteringRadiusUncertainties,
                CompactRMatrixLimited > {

  friend CompactCovarianceBase<
             CompactRMatrixLimitedUncertainties,
             ReichMooreScatteringRadiusUncertainties,
             CompactRMatrixLimited >;

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
  CompactRMatrixLimited() = default;
  #endif

  /**
   *  @brief Constructor with scattering radius uncertainty
   *
   *  @param[in] ifg           flag to indicate whether or not the widths are reduced
   *  @param[in] dap           the scattering radius uncertainty data
   *  @param[in] parameters    the resonance parameters and uncertainties
   *  @param[in] matrix        the correlation matrix
   */
  CompactRMatrixLimited( bool ifg,
                         ReichMooreScatteringRadiusUncertainties&& dap,
                         CompactRMatrixLimitedUncertainties&& parameters,
                         CompactCorrelationMatrix&& matrix )
    try : CompactCovarianceBase( 0., 0., std::move( dap ),
                                 static_cast< long >( ifg ),
                                 parameters.NJSX(),
                                 std::move( parameters ), std::move( matrix ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance and covariance "
                 "parameters in the R-Matrix limited representation for the compact "
                 "covariance format (LCOMP = 2)" );
      throw;
    }

  /**
   *  @brief Constructor without scattering radius uncertainty
   *
   *  @param[in] ifg           flag to indicate whether or not the widths are reduced
   *  @param[in] parameters    the resonance parameters and uncertainties
   *  @param[in] matrix        the correlation matrix
   */
  CompactRMatrixLimited( bool ifg,
                         CompactRMatrixLimitedUncertainties&& parameters,
                         CompactCorrelationMatrix&& matrix )
    try : CompactCovarianceBase( 0., 0.,
                                 static_cast< long >( ifg ),
                                 parameters.NJSX(),
                                 std::move( parameters ),
                                 std::move( matrix ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance and covariance "
                 "parameters in the R-Matrix limited representation for the compact "
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
  CompactRMatrixLimited( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT )
    try : CompactCovarianceBase( it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance and covariance "
                 "parameters in the R-Matrix limited representation for the compact "
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
  static constexpr int representation() { return 7; }

  /**
   *  @brief Return whether or not the widths are reduced or not
   */
  bool IFG() const { return CompactCovarianceBase::L1(); }

  /**
   *  @brief Return whether or not the widths are reduced or not
   */
  bool reducedWidths() const { return this->IFG(); }

  /**
   *  @brief Return the number of spin groups
   */
  unsigned int NJS() const { return CompactCovarianceBase::N1(); }

  /**
   *  @brief Return the number of spin groups
   */
  unsigned int numberSpinGroups() const { return this->NJS(); }

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
