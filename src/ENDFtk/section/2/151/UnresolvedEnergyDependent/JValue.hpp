/**
 *  @class
 *  @brief Unresolved resonance data associated to a given angular momentum
 *         value J with fully energy dependent widths (this is the most
 *         general case for unresolved resonances).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT JValue : protected ListRecord {

  /* auxiliary functions */

  static std::vector< double >
  generateList( double amux, double amun, double amug, double amuf,
                std::vector< double >&& energies,
                std::vector< double >&& d,
                std::vector< double >&& gx,
                std::vector< double >&& gn,
                std::vector< double >&& gg,
                std::vector< double >&& gf ) {

    std::vector< double > list{ 0.0, 0.0, amux, amun , amug , amuf  };

    unsigned int ne = energies.size();
    if ( ( d.size() != ne ) or ( gx.size() != ne ) or
         ( gn.size() != ne ) or ( gg.size() != ne ) or ( gf.size() != ne ) ) {

      Log::info( "The number of energies and the resonance parameters are not "
                 "consistent" );
      Log::info( "NE value: {}", ne );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "d.size(): {}", d.size() );
      Log::info( "gx.size(): {}", gx.size() );
      Log::info( "gn.size(): {}", gn.size() );
      Log::info( "gg.size(): {}", gg.size() );
      Log::info( "gf.size(): {}", gf.size() );
      throw std::exception();
    }

    for ( unsigned int i = 0; i < ne; ++i ) {

      list.push_back( energies[i] );
      list.push_back( d[i] );
      list.push_back( gx[i] );
      list.push_back( gn[i] );
      list.push_back( gg[i] );
      list.push_back( gf[i] );
    }
    return list;
  }

  static void
  verifySize( unsigned int NPL, unsigned int NE ) {

    if ( NE == 0 ) {

      Log::error( "There must be at least one set of resonance parameters" );
      Log::info( "Expected NE > 0 but found {}", NE );
      throw std::exception();
    }

    if ( NPL != 6 + NE * 6 ) {

      Log::error( "The resonance parameters must be given as multiples of 6" );
      Log::info( "Expected NPL=(NE+1)*6, found NPL={} for NE={}", NPL, NE );
      throw std::exception();
    }
  }

  auto column( const int index ) const {

    using namespace njoy::tools;
    return
      ListRecord::list()
        | std20::views::drop( index + 6 )
        | std23::views::stride(6);
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  JValue( ListRecord&& list ) : ListRecord( std::move( list ) ) {

    verifySize( ListRecord::NPL(), this->NE() );
  }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] spin        the spin
   *  @param[in] amun        the degrees of freedom for the neutron width
   *  @param[in] amug        the degrees of freedom for the gamma width
   *  @param[in] amuf        the degrees of freedom for the fission width
   *  @param[in] amux        the degrees of freedom for the competitive width
   *  @param[in] inter       the interpolation scheme for the cross sections
   *  @param[in] energies    the energy values (NE values)
   *  @param[in] d           the level spacings (NE values)
   *  @param[in] gn          the average neutron widths (NE values)
   *  @param[in] gg          the average gamma widths (NE values)
   *  @param[in] gf          the average fission widths (NE values)
   *  @param[in] gx          the average competitive widths (NE values)
   */
  JValue( double spin, double amun, double amug, double amuf, double amux, int inter,
          std::vector< double >&& energies,
          std::vector< double >&& d,
          std::vector< double >&& gn,
          std::vector< double >&& gg,
          std::vector< double >&& gf,
          std::vector< double >&& gx )
    try :  JValue( ListRecord( spin, 0.0, inter, 0, energies.size(),
                               generateList( amux, amun, amug, amuf,
                                             std::move( energies ),
                                             std::move( d ),
                                             std::move( gx ),
                                             std::move( gn ),
                                             std::move( gg ),
                                             std::move( gf ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing J value resonance "
                 "parameters in the unresolved Single Level Breit-Wigner "
                 "representation using energy dependent widths" );
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
                 "representation using energy dependent widths" );
      throw;
    }

  /**
   *  @brief Return the spin value
   */
  double AJ() const { return ListRecord::C1(); }

  /**
   *  @brief Return the spin value
   */
  double spin() const { return this->AJ(); }

  /**
   *  @brief Return the number of degrees of freedom for the neutron width.
   */
  double AMUN() const { return ListRecord::list()[3]; }

  /**
   *  @brief Return the number of degrees of freedom for the neutron width.
   */
  double neutronWidthDegreesFreedom() const { return this->AMUN(); }

  /**
   *  @brief Return the number of degrees of freedom for the gamma width.
   */
  double AMUG() const { return ListRecord::list()[4]; }

  /**
   *  @brief Return the number of degrees of freedom for the gamma width.
   */
  double gammaWidthDegreesFreedom() const { return JValue::AMUG(); }

  /**
   *  @brief Return the number of degrees of freedom for the fission width.
   */
  double AMUF() const { return ListRecord::list()[5]; }

  /**
   *  @brief Return the number of degrees of freedom for the fission width.
   */
  double fissionWidthDegreesFreedom() const { return JValue::AMUF(); }

  /**
   *  @brief Return the number of degrees of freedom for the competitive width.
   */
  double AMUX() const { return ListRecord::list()[2]; }

  /**
   *  @brief Return the number of degrees of freedom for the competitive width.
   */
  double competitiveWidthDegreesFreedom() const { return JValue::AMUX(); }

  /**
   *  @brief Return the energy values.
   */
  auto ES() const { return this->column( 0 ); }

  /**
   *  @brief Return the energy values.
   */
  auto energies() const { return this->ES(); }

  /**
   *  @brief Return the average level spacing.
   */
  auto D() const { return this->column( 1 ); }

  /**
   *  @brief Return the average level spacing.
   */
  auto averageLevelSpacings() const { return this->D(); }

  /**
   *  @brief Return the average neutron width.
   */
  auto GN() const { return this->column( 3 ); }

  /**
   *  @brief Return the average neutron width.
   */
  auto averageNeutronWidths() const { return this->GN(); }

  /**
   *  @brief Return the average gamma width.
   */
  auto GG() const { return this->column( 4 ); }

  /**
   *  @brief Return the average gamma width.
   */
  auto averageGammaWidths() const { return this->GG(); }

  /**
   *  @brief Return the average fission widths (energy dependent).
   */
  auto GF() const { return this->column( 5 ); }

  /**
  *  @brief Return the average fission widths (energy dependent).
   */
  auto averageFissionWidths() const { return JValue::GF(); }

  /**
   *  @brief Return the average competitive width.
   */
  auto GX() const { return this->column( 2 ); }

  /**
  *  @brief Return the average competitive width.
   */
  auto averageCompetitiveWidths() const { return JValue::GX(); }

  /**
   *  @brief Return the interpolation type.
   */
  int INT() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of energy points.
   */
  unsigned int NE() const { return this->energies().size(); }

  /**
   *  @brief Return the number of interpolation ranges (always 1).
   */
  static constexpr int NR() { return 1; }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const {

    return std::array< int, 1 >{ this->INT() };
  }

  /**
   *  @brief Return the interpolation range boundaries.
   */
  auto boundaries() const {

    return std::array< int, 1 >{ static_cast<int>( this->NE() ) };
  }

  using ListRecord::NC;
  using ListRecord::print;
};
