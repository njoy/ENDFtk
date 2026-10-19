/**
 *  @class
 *  @brief Unresolved resonance relative covariance data
 *
 *  The UnresolvedRelativeCovariances class is used to represent the covariance
 *  data in the unresolved resonance region. It is the ONLY unresolved resonance
 *  representation thus far.
 *
 *  See ENDF102, section 32.2.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT UnresolvedRelativeCovariances {

public:

  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/JValue.hpp"
  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/LValue.hpp"
  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/CovarianceMatrix.hpp"

private:

  /* fields */

  double spi_;
  double ap_;
  std::vector< LValue > lvalues_;
  CovarianceMatrix matrix_;

  /* auxiliary functions */

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  UnresolvedRelativeCovariances( double spi, double ap,
                                 std::vector< LValue >&& lvalues,
                                 Iterator& it, const Iterator& end, long& lineNumber,
                                 int MAT, int MF, int MT ) :
    UnresolvedRelativeCovariances( spi, ap, std::move( lvalues ),
                                   CovarianceMatrix( it, end, lineNumber,
                                                     MAT, MF, MT ) ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  UnresolvedRelativeCovariances( ControlRecord&& cont,
                                 Iterator& it, const Iterator& end, long& lineNumber,
                                 int MAT, int MF, int MT ) :
    UnresolvedRelativeCovariances( cont.C1(), cont.C2(),
                                   readSequence< LValue >( it, end, lineNumber,
                                                           MAT, MF, MT,
                                                           cont.N1() ),
                                   it, end, lineNumber, MAT, MF, MT ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  UnresolvedRelativeCovariances() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] spi       the target spin value
   *  @param[in] ap        the scattering radius
   *  @param[in] lvalues   the l values and the resonance parameters
   *  @param[in] matrix    the covariance matrix
   */
  UnresolvedRelativeCovariances( double spi, double ap,
                                 std::vector< LValue >&& lvalues,
                                 CovarianceMatrix&& matrix ) :
      // no need for a try ... catch: nothing can go wrong here
      spi_( spi ), ap_( ap ), lvalues_( std::move( lvalues ) ),
      matrix_( std::move( matrix ) ) {}

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
  UnresolvedRelativeCovariances(
      Iterator& it, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT ) :
    UnresolvedRelativeCovariances(
        ControlRecord( it, end, lineNumber, MAT, MF, MT ),
        it, end, lineNumber, MAT, MF, MT ) {}

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int LRU() { return 2; }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  constexpr int type() const { return this->LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  constexpr int representation() const { return this->LRF(); }

  /**
   *  @brief Return the average fission flag
   */
  bool LFW() const {

    return this->covarianceMatrix().MPAR() < 5 ? false : true;
  }

  /**
  *  @brief Return the average fission flag
  */
  bool averageFissionWidthFlag() const {

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
   *  @brief Return the number of l values for which data is available
   */
  int NLS() const { return this->lvalues_.size(); }

  /**
   *  @brief Return the number of l values for which data is available
   */
  int numberLValues() const { return this->NLS(); }

  /**
   *  @brief Return the resonance parameter uncertainties
   */
  auto lValues() const {

    using namespace njoy::tools;
    return std20::views::all( this->lvalues_ );
  }

  /**
   *  @brief Return the covariance matrix
   */
  const CovarianceMatrix& covarianceMatrix() const {

    return this->matrix_;
  }

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const {

    long NC = 1 + this->covarianceMatrix().NC();
    for ( const auto& lvalue : this->lValues() ) { NC += lvalue.NC(); }
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
                   0, 0,
                   this->NLS(), 0 ).print( it, MAT, MF, MT );
    for ( const auto& lvalue : this->lValues() ) {

      lvalue.print( it, MAT, MF, MT );
    }
    this->covarianceMatrix().print( it, MAT, MF, MT );
  }
};
