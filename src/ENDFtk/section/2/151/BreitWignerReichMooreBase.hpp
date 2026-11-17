/**
 *  @class
 *  @brief Base class for Breit-Wigner and Reich-Moore resonance representations
 *
 *  The BreitWignerReichMooreBase class is used to represent the SLBW, MLBW and
 *  RM resonance representations (LRU=1 and LRF=1, 2 or 3) from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.1 and 2.2.1.2 for more information.
 */
template < typename LValue, typename Derived >
class BreitWignerReichMooreBase {

  /* fields */

  double spi_;
  double ap_;
  bool lad_;
  int nlsc_;

  std::vector< LValue > lvalues_;

  /* auxiliary functions */

  static void
  verifySize( int NLS ) {

    if ( NLS < 1 ) {

      Log::error( "Encountered illegal NLS value" );
      Log::info( "NLS should be larger than zero" );
      Log::info( "NLS value: {}", NLS );
      throw std::exception();
    }
  }

protected:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  BreitWignerReichMooreBase() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] spi       the target spin value
   *  @param[in] ap        the scattering radius
   *  @param[in] lad       the angular distributions flag
   *  @param[in] nlsc      the number of l values for convergence
   *  @param[in] lvalues   the l values and the resonance parameters
   */
  BreitWignerReichMooreBase( double spi, double ap, bool lad, int nlsc,
                             std::vector< LValue >&& lvalues ) :
      // no need for a try ... catch: nothing can go wrong here
      spi_( spi ), ap_( ap ), lad_( lad ), nlsc_( nlsc ),
      lvalues_( std::move( lvalues ) ) {

        verifySize( this->NLS() );
      }

  private:
  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  BreitWignerReichMooreBase( ControlRecord&& cont,
                             Iterator& it, const Iterator& end, long& lineNumber,
                             int MAT, int MF, int MT ) :
     // no try ... catch: exceptions will be handled in the derived class
    BreitWignerReichMooreBase( cont.C1(), cont.C2(), cont.L1(), cont.N2(),
                               readSequence< LValue >(
                                   it, end, lineNumber,
                                   MAT, MF, MT, cont.N1() ) ) {}

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
   BreitWignerReichMooreBase( Iterator& it, const Iterator& end, long& lineNumber,
                              int MAT, int MF, int MT ) :
     // no try ... catch: exceptions will be handled in the derived class
     BreitWignerReichMooreBase(
       ControlRecord( it, end, lineNumber, MAT, MF, MT ),
       it, end, lineNumber, MAT, MF, MT ) {}

public:

  /* get methods */

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
  constexpr bool LFW() const { return false; }

  /**
  *  @brief Return the average fission flag
  */
  constexpr int averageFissionWidthFlag() const {

    return BreitWignerReichMooreBase::LFW();
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
   *  @brief Return the angular distribution flag
   */
  bool LAD() const { return this->lad_; }

  /**
   *  @brief Return the angular distribution flag
   */
  bool angularDistributionsFlag() const { return this->LAD(); }

  /**
   *  @brief Return the number of l values for which resonance parameters are
   *         given
   */
  int NLS() const { return this->lvalues_.size(); }

  /**
   *  @brief Return the number of l values for which resonance parameters are
   *         given
   */
  int numberLValues() const { return this->NLS(); }

  /**
   *  @brief Return the number of l values required for convergence of
   *         angular distributions
   */
  int NLSC() const { return this->nlsc_; }

  /**
   *  @brief Return the number of l values required for convergence of
   *         angular distributions
   */
  int numberLValuesForDistributions() const { return this->NLSC(); }

  /**
   *  @brief Return the l values and its resonance parameters
   */
  auto lValues() const {

    using namespace njoy::tools;
    return this->lvalues_ | std20::views::all;
  }

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const {

    long NC = 1;
    for ( const auto& lvalue : this->lvalues_ ) { NC += lvalue.NC(); }
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
                   this->LAD(), 0,
                   this->NLS(), this->NLSC() ).print( it, MAT, MF, MT );
    for ( const auto& lvalue : this->lvalues_ ) {

      lvalue.print( it, MAT, MF, MT );
    }
  }
};
