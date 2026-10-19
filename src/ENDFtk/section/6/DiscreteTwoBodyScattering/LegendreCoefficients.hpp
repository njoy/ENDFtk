/**
 *  @class
 *  @brief An angular distribution given as Legendre coefficients
 *
 *  The LegendreCoefficients class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as Legendre coefficients.
 *
 *  This component is similar to the MF4 component of the same name (with the
 *  exception that this is ListRecord based).
 *
 *  See ENDF102, section 6.2.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT LegendreCoefficients : protected ListRecord {

  /* auxiliary functions */

  static void
  verifyLANG( int LANG ) {

    if ( LANG != 0 ) {

      Log::error( "Encountered illegal LANG value" );
      Log::info( "LANG must be equal to 0 for legendre coefficients" );
      Log::info( "LANG value: {}", LANG );
      throw std::exception();
    }
  }

  static void
  verifySize( int NW, int NL ) {

    if ( NW != NL ) {

      Log::error( "Encountered illegal NW and NL values" );
      Log::info( "NW must be equal to NL for legendre coefficients" );
      Log::info( "NW value: {}", NW );
      Log::info( "NL value: {}", NL );
      throw std::exception();
    }
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  LegendreCoefficients() = default;
  #endif

  /**
   *  @brief Private constructor
   */
  LegendreCoefficients( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

      verifyLANG( this->L1() );
      verifySize( this->NW(), this->NL() );
  };

  /**
   *  @brief Constructor
   *
   *  @param[in] energy          the incident energy value
   *  @param[in] coefficients    the coefficients
   */
  LegendreCoefficients( double energy, std::vector< double >&& coefficients ) :
    // this can never fail, try-catch would be unreachable
    LegendreCoefficients( ListRecord( 0.0, energy, 0, 0,
                                      coefficients.size(),
                                      std::move( coefficients ) ) ) {}

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
  LegendreCoefficients( Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT )
    try : LegendreCoefficients(
            ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading Legendre coefficients "
                 "(LAW=2 LANG=0)" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the LANG value
   */
  static constexpr int LANG() { return 0; }

  /**
   *  @brief Return the number of values (equal to the Legendre order)
   */
  long NW() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the Legendre order for the angular distribution (equal to
   *         the number of coefficients in the distribution)
   */
  int NL() const { return ListRecord::N2(); }

  /**
   *  @brief Return the Legendre order for the angular distribution (equal to
   *         the number of coefficients in the distribution)
   */
  int legendreOrder() const { return this->NL(); }

  /**
   *  @brief Return the Legendre coefficients in the distribution (a0 is not
   *         present and assumed to be equal to 1)
   */
  auto A() const { return ListRecord::list(); }

  /**
   *  @brief Return the Legendre coefficients in the distribution (a0 is not
   *         present and assumed to be equal to 1)
   */
  auto coefficients() const { return this->A(); }

  using ListRecord::NC;
  using ListRecord::print;
};
