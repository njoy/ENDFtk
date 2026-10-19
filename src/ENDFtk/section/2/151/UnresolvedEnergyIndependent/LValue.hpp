/**
 *  @class
 *  @brief The unresolved resonance parameters for a given l value in the SLBW
 *         representation for independent widths (with no fission given)
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT LValue : protected ListRecord {

  /* auxiliary functions */

  static void
  verifySize( int NPL, int NJS ) {

    if ( NPL != 6 * NJS ) {

      Log::error( "Encountered inconsistent list size" );
      Log::info( "NPL must be equal to 6 * NJS" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NJS value: {}", NJS );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( std::vector< double >&& spins,
                std::vector< double >&& d,
                std::vector< double >&& amun,
                std::vector< double >&& gn,
                std::vector< double >&& gg ) {

    std::vector< double > list;
    unsigned int njs = spins.size();
    if ( ( d.size() != njs ) or ( amun.size() != njs ) or
         ( gn.size() != njs ) or ( gg.size() != njs ) ) {

      Log::info( "The number of spin values and the resonance parameters are not "
                 "consistent" );
      Log::info( "NJS value: {}", njs );
      Log::info( "spins.size(): {}", spins.size() );
      Log::info( "d.size(): {}", d.size() );
      Log::info( "amun.size(): {}", amun.size() );
      Log::info( "gn.size(): {}", gn.size() );
      Log::info( "gg.size(): {}", gg.size() );
      throw std::exception();
    }

    for ( unsigned int i = 0; i < njs; ++i ) {

      list.push_back( d[i] );
      list.push_back( spins[i] );
      list.push_back( amun[i] );
      list.push_back( gn[i] );
      list.push_back( gg[i] );
      list.push_back( 0.0 );
    }
    return list;
  }

  /* workaround for the removal of range-v3 */

  // using std20::views::repeat in C++ works but causes issues on the Python side
  std::vector< double > zeros_;

  void generateZeros() {

    this->zeros_ = std::vector( this->NJS(), 0.0 );
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  LValue( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifySize( this->NPL(), this->N2() );
    generateZeros();
  }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] awri       the atomic weight ratio
   *  @param[in] l          the orbital angular momentum value
   *  @param[in] spins      the spin values (NJS values)
   *  @param[in] spacing    the level spacing values (NJS values)
   *  @param[in] amun       the degrees of freedom for the neutron width (NJS
   *                        values)
   *  @param[in] gn         the average neutron widths (NJS values)
   *  @param[in] gg         the average gamma widths (NJS values)
   */
  LValue( double awri, int l,
          std::vector< double >&& spins,
          std::vector< double >&& spacing,
          std::vector< double >&& amun,
          std::vector< double >&& gn,
          std::vector< double >&& gg )
    try :  LValue( ListRecord( awri, 0.0, l, 0.0, spins.size(),
                               generateList( std::move( spins ),
                                             std::move( spacing ),
                                             std::move( amun ),
                                             std::move( gn ),
                                             std::move( gg ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing l value resonance "
                 "parameters in the unresolved Single Level Breit-Wigner "
                 "representation" );
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
  LValue( Iterator& it, const Iterator& end, long& lineNumber,
          int MAT, int MF, int MT )
    try : LValue( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing l value resonance "
                 "parameters in the unresolved Single Level Breit-Wigner "
                 "representation" );
      throw;
    }

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double AWRI() const { return ListRecord::C1(); }

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double atomicWeightRatio() const { return this->AWRI(); }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int L() const { return ListRecord::L1(); }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int orbitalMomentum() const { return this->L(); }

  /**
   *  @brief Return the number of J values for this l value
   */
  int NJS() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of J values for this l value
   */
  int numberSpinValues() const { return this->NJS(); }

  /**
   *  @brief Return the data for each of the J values
   */
  auto jValues() const {

    using namespace njoy::tools;
    auto chunked = ListRecord::list() | std23::views::chunk( 6 );
    using Range = decltype( chunked[0] );
    return chunked | std20::views::transform(
                       [] ( Range&& chunk ) -> JValue< Range >
                          { return { std::move( chunk ) }; } );
  }

  /**
   *  @brief Return the average level spacing values
   */
  auto D() const {

    using namespace njoy::tools;
    return this->jValues()
             | std20::views::transform( [] ( const auto& jvalue )
                                           { return jvalue.D(); } );
  }

  /**
   *  @brief Return the average level spacing values
   */
  auto averageLevelSpacings() const { return this->D(); }

  /**
   *  @brief Return the spin values
   */
  auto AJ() const {

    using namespace njoy::tools;
    return this->jValues()
             | std20::views::transform( [] ( const auto& jvalue )
                                           { return jvalue.AJ(); } );
  }

  /**
  *  @brief Return the spin values
   */
  auto spinValues() const { return this->AJ(); }

  /**
   *  @brief Return the degrees of freedom for the neutron width
   */
  auto AMUN() const {

    using namespace njoy::tools;
    return this->jValues()
             | std20::views::transform( [] ( const auto& jvalue )
                                           { return jvalue.AMUN(); } );
  }

  /**
   *  @brief Return the degrees of freedom for the neutron width
   */
  auto neutronWidthDegreesFreedom() const { return this->AMUN(); }

  /**
   *  @brief Return the degrees of freedom for the gamma width
   */
  auto AMUG() const {

    // see note above about range-v3 removal workaround
    // using namespace njoy::tools;
    // return std20::views::repeat_n( 0.0, this->NJS() );
    using namespace njoy::tools;
    return std20::views::all( this->zeros_ );
  }

  /**
   *  @brief Return the degrees of freedom for the gamma width
   */
  auto gammaWidthDegreesFreedom() const { return this->AMUG(); }

  /**
   *  @brief Return the degrees of freedom for the fission width
   */
  auto AMUF() const {

    // see note above about range-v3 removal workaround
    // using namespace njoy::tools;
    // return std20::views::repeat_n( 0.0, this->NJS() );
    using namespace njoy::tools;
    return std20::views::all( this->zeros_ );
  }

  /**
   *  @brief Return the degrees of freedom for the fission width
   */
  auto fissionWidthDegreesFreedom() const { return this->AMUG(); }

  /**
   *  @brief Return the degrees of freedom for the competitive width
   */
  auto AMUX() const {

    // see note above about range-v3 removal workaround
    // using namespace njoy::tools;
    // return std20::views::repeat_n( 0.0, this->NJS() );
    using namespace njoy::tools;
    return std20::views::all( this->zeros_ );
  }

  /**
   *  @brief Return the degrees of freedom for the competitive width
   */
  auto competitiveWidthDegreesFreedom() const { return this->AMUG(); }

  /**
   *  @brief Return the average neutron width values.
   */
  auto GN() const {

    using namespace njoy::tools;
    return this->jValues()
             | std20::views::transform( [] ( const auto& jvalue )
                                           { return jvalue.GN(); } );
  }

  /**
   *  @brief Return the average neutron width values.
   */
  auto averageNeutronWidths() const { return this->GN(); }

  /**
   *  @brief Return the average gamma width values.
   */
  auto GG() const {

    using namespace njoy::tools;
    return this->jValues()
             | std20::views::transform( [] ( const auto& jvalue )
                                           { return jvalue.GG(); } );
  }

  /**
   *  @brief Return the average gamma width values.
   */
  auto averageGammaWidths() const { return this->GG(); }

  /**
   *  @brief Return the average fission width values.
   */
  auto GF() const {

    // see note above about range-v3 removal workaround
    // using namespace njoy::tools;
    // return std20::views::repeat_n( 0.0, this->NJS() );
    using namespace njoy::tools;
    return this->zeros_ | std20::views::all;
  }

  /**
   *  @brief Return the average fission width values.
   */
  auto averageFissionWidths() const { return this->GF(); }

  /**
   *  @brief Return the average competitive width values.
   */
  auto GX() const {

    // see note above about range-v3 removal workaround
    // using namespace njoy::tools;
    // return std20::views::repeat_n( 0.0, this->NJS() );
    using namespace njoy::tools;
    return std20::views::all( this->zeros_ );
  }

  /**
   *  @brief Return the average competitive width values.
   */
  auto averageCompetitiveWidths() const { return this->GX(); }

  using ListRecord::NC;
  using ListRecord::print;
};
