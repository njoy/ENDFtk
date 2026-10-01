/**
 *  @class
 *  @brief Unresolved resonance data associated to a given angular momentum
 *         value J when only the fission width is energy dependent.
 *
 *  This JValue class applies to the case of energy dependent fission widths
 *  while all other widths are energy independent.
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT JValue : protected ListRecord {

  /* auxiliary functions */

  static std::vector< double >
  generateList( double spin,
                double d,
                double amun,
                double gn,
                double gg,
                std::vector< double >&& gf ) {

    std::vector< double > list{ d, spin,  amun,
                                gn, gg, 0.0 };
    list.insert( list.end(), gf.begin(), gf.end() );
    return list;
  }

  static void
  verifySize( unsigned int NE ) {

    if ( NE < 1 ) {

      Log::error( "There appear to be no energy dependent fission widths given" );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  JValue( ListRecord&& list ) : ListRecord( std::move( list ) ) {

    verifySize( this->NE() );
  }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] l          the orbital angular momentum value
   *  @param[in] spin       the spin
   *  @param[in] d          the level spacing
   *  @param[in] amun       the degrees of freedom for the neutron width
   *  @param[in] amuf       the degrees of freedom for the fission width
   *  @param[in] gn         the average neutron width
   *  @param[in] gg         the average gamma width
   *  @param[in] gf         the average fission widths
   */
  JValue( int l, double spin, double d, double amun, int amuf,
          double gn, double gg, std::vector< double >&& gf )
    try :  JValue( ListRecord( 0.0, 0.0, l, amuf, 0,
                               generateList( spin, d, amun, gn, gg,
                                             std::move( gf ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing J value resonance "
                 "parameters in the unresolved Single Level Breit-Wigner "
                 "representation using energy dependent fission widths" );
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
  JValue( Iterator& it, const Iterator& end, long& lineNumber,
          int MAT, int MF, int MT )
    try : JValue( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing J value resonance "
                 "parameters in the unresolved Single Level Breit-Wigner "
                 "representation using energy dependent fission widths" );
      throw;
    }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int L() const { return ListRecord::L1(); }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int orbitalMomentum() const { return this->L(); }

  /**
   *  @brief Return the spin value
   */
  double AJ() const { return ListRecord::list()[1]; }

  /**
   *  @brief Return the spin value
   */
  double spin() const { return this->AJ(); }

  /**
   *  @brief Return the number of degrees of freedom for the neutron width.
   */
  double AMUN() const { return ListRecord::list()[2]; }

  /**
   *  @brief Return the number of degrees of freedom for the neutron width.
   */
  double neutronWidthDegreesFreedom() const { return this->AMUN(); }

  /**
   *  @brief Return the number of degrees of freedom for the gamma width.
   */
  static constexpr double AMUG() { return 0.0; }

  /**
   *  @brief Return the number of degrees of freedom for the gamma width.
   */
  static constexpr double gammaWidthDegreesFreedom() { return JValue::AMUG(); }

  /**
   *  @brief Return the number of degrees of freedom for the fission width.
   */
  int AMUF() const { return ListRecord::L2(); }

  /**
   *  @brief Return the number of degrees of freedom for the fission width.
   */
  int fissionWidthDegreesFreedom() const { return JValue::AMUF(); }

  /**
   *  @brief Return the number of degrees of freedom for the competitive width.
   */
  static constexpr double AMUX() { return 0.0; }

  /**
   *  @brief Return the number of degrees of freedom for the competitive width.
   */
  static constexpr double competitiveWidthDegreesFreedom() {

    return JValue::AMUX();
  }

  /**
   *  @brief Return the average level spacing.
   */
  double D() const { return ListRecord::list()[0]; }

  /**
   *  @brief Return the average level spacing.
   */
  double averageLevelSpacing() const { return this->D(); }

  /**
   *  @brief Return the average neutron width.
   */
  double GN() const { return ListRecord::list()[3]; }

  /**
   *  @brief Return the average neutron width.
   */
  double averageNeutronWidth() const { return this->GN(); }

  /**
   *  @brief Return the average gamma width.
   */
  double GG() const { return ListRecord::list()[4]; }

  /**
   *  @brief Return the average gamma width.
   */
  double averageGammaWidth() const { return this->GG(); }

  /**
   *  @brief Return the average competitive width.
   */
  static constexpr double GX() { return 0.0; }

  /**
  *  @brief Return the average competitive width.
   */
  static constexpr double averageCompetitiveWidth() { return JValue::GX(); }

  /**
   *  @brief Return the average fission widths (energy dependent).
   */
  auto GF() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 6 );
  }

  /**
  *  @brief Return the average fission widths (energy dependent).
   */
  auto averageFissionWidths() const {

    return JValue::GF();
  }

  /**
   *  @brief Return the number of average fission width points.
   */
  unsigned int NE() const { return this->GF().size(); }

  /**
   *  @brief Return the number of interpolation ranges (always 1).
   */
  static constexpr int NR() { return 1; }

  /**
   *  @brief Return the interpolants (always linear-linear).
   */
  static constexpr auto interpolants() { return std::array< int, 1 >{ 2 }; }

  /**
   *  @brief Return the interpolation range boundaries.
   */
  auto boundaries() const {

    return std::array< int, 1 >{ static_cast<int>( this->NE() ) };
  }

  using ListRecord::NC;
  using ListRecord::print;
};
