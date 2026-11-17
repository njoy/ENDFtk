/**
 *  @class
 *  @brief Base class for the unresolved resonance paraneters
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
template < typename Derived,
           typename LValue = typename LJValueType< Derived >::LType >
class UnresolvedBase : public UnresolvedBaseWithoutSpin< Derived, LValue > {

  /* fields */

  double spi_;
  double ap_;
  bool lssf_;

protected:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  UnresolvedBase() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] spi       the target spin value
   *  @param[in] ap        the scattering radius
   *  @param[in] lssf      the self-shielding only flag
   *  @param[in] lvalues   the l values and the resonance parameters
   */
  UnresolvedBase( double spi, double ap, bool lssf,
                  std::vector< LValue >&& lvalues ) :
      // no need for a try ... catch: nothing can go wrong here
      UnresolvedBaseWithoutSpin< Derived >( std::move( lvalues ) ),
      spi_( spi ), ap_( ap ), lssf_( lssf ) {}

  private:
  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  UnresolvedBase( ControlRecord&& cont,
                  Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT ) :
    UnresolvedBase( cont.C1(), cont.C2(), cont.L1(),
                    readSequence< LValue >( it, end, lineNumber,
                                            MAT, MF, MT, cont.N1() ) ) {}

  public:
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
  UnresolvedBase( Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT ) :
    UnresolvedBase( ControlRecord( it, end, lineNumber, MAT, MF, MT ),
                    it, end, lineNumber, MAT, MF, MT ) {}

public:

  /* get methods */

  /**
   *  @brief Return the target spin
   */
  double SPI() const { return this->spi_; }

  /**
   *  @brief Return the scattering radius
   */
  double AP() const { return this->ap_; }

  /**
   *  @brief Return the self-shielding only flag
   */
  bool LSSF() const { return this->lssf_; }

  using UnresolvedBaseWithoutSpin< Derived >::type;
  using UnresolvedBaseWithoutSpin< Derived >::representation;
  using UnresolvedBaseWithoutSpin< Derived >::averageFissionWidthFlag;
  using UnresolvedBaseWithoutSpin< Derived >::spin;
  using UnresolvedBaseWithoutSpin< Derived >::scatteringRadius;
  using UnresolvedBaseWithoutSpin< Derived >::selfShieldingOnly;
  using UnresolvedBaseWithoutSpin< Derived >::NLS;
  using UnresolvedBaseWithoutSpin< Derived >::numberLValues;
  using UnresolvedBaseWithoutSpin< Derived >::lValues;

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const {

    long NC = 1;
    for ( const auto& lvalue : this->lValues() ) { NC += lvalue.NC(); }
    return NC;
  };

  /**
   *  @brief Print this MF2 MT151 component
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
                   this->LSSF(), 0,
                   this->NLS(), 0 ).print( it, MAT, MF, MT );
    for ( const auto& lvalue : this->lValues() ) {

      lvalue.print( it, MAT, MF, MT );
    }
  }
};
