/**
 *  @class
 *  @brief Short-range limited R-matrix resonance parameters and covariance data
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ShortRangeRMatrixLimitedBlock {

public:

  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/ResonanceParameters.hpp"
  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/CovarianceMatrix.hpp"

private:

  /* fields */

  std::vector< ResonanceParameters > parameters_;
  CovarianceMatrix covariance_;

  /* auxiliary functions */

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  ShortRangeRMatrixLimitedBlock( std::vector< ResonanceParameters >&& parameters,
                                 Iterator& begin,
                                 const Iterator& end,
                                 long& lineNumber,
                                 int MAT, int MF, int MT ) :
    ShortRangeRMatrixLimitedBlock( std::move( parameters ),
                                   CovarianceMatrix( begin, end, lineNumber,
                                                     MAT, MF, MT ) ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  ShortRangeRMatrixLimitedBlock( ControlRecord&& cont,
                                 Iterator& begin,
                                 const Iterator& end,
                                 long& lineNumber,
                                 int MAT, int MF, int MT ) :
    ShortRangeRMatrixLimitedBlock(
        readSequence< ResonanceParameters >( begin, end, lineNumber,
                                             MAT, MF, MT, cont.L1() ),
        begin, end, lineNumber, MAT, MF, MT ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ShortRangeRMatrixLimitedBlock() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] parameters     the resonance parameters
   *  @param[in] covariances    the covariance matrix
   */
  ShortRangeRMatrixLimitedBlock( std::vector< ResonanceParameters >&& parameters,
                                 CovarianceMatrix&& covariances ) :
    parameters_( std::move( parameters ) ),
    covariance_( std::move( covariances ) ) {}

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
  ShortRangeRMatrixLimitedBlock(
          Iterator& it, const Iterator& end, long& lineNumber,
          int MAT, int MF, int MT )
    try : ShortRangeRMatrixLimitedBlock( ControlRecord( it, end, lineNumber,
                                                        MAT, MF, MT ),
                                         it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing short range resonance and "
                 "covariance parameters in the R-matrix limited representation" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the number of spin groups for which resonance parameters
   *         are given
   */
  int NJSX() const { return this->parameters_.size(); }

  /**
   *  @brief Return the number of spin groups for which resonance parameters
   *         are given
   */
  int numberSpinGroups() const { return this->NJSX(); }

  /**
   *  @brief Return the resonance parameters
   */
  auto resonanceParameters() const {

    using namespace njoy::tools;
    return std20::views::all( this->parameters_ );
  }

  /**
   *  @brief Return the covariance matrix
   */
  const CovarianceMatrix& covarianceMatrix() const {

    return this->covariance_;
  }

  /**
   *  @brief Return the number of lines in this MF32 MT151 component
   */
  long NC() const {

    long NC = 1;
    for ( const auto& group : this->parameters_ ) { NC += group.NC(); }
    NC += this->covariance_.NC();
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

    ControlRecord( 0., 0., this->NJSX(), 0, 0, 0 ).print( it, MAT, MF, MT );
    for ( const auto& group : this->parameters_ ) {

      group.print( it, MAT, MF, MT );
    }
    this->covariance_.print( it, MAT, MF, MT );
  }
};
