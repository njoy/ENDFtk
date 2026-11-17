/**
 *  @class
 *  @brief An angular distribution given as Legendre coefficients
 *
 *  The LegendreCoefficients class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as Legendre coefficients.
 *
 *  See ENDF102, section 4.2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT LegendreCoefficients : protected ListRecord {

  /* auxiliary functions */

  /* constructor */

  /** 
   *  @brief Private intermediate constructor
   */
  LegendreCoefficients( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] energy         the incident energy
   *  @param[in] coefficients   the Legendre coefficients
   */
  LegendreCoefficients( double energy, std::vector< double >&& list ) :
    // no try-catch because it would be unreachable
    LegendreCoefficients( ListRecord( 0.0, energy, 0, 0, 0,
                                      std::move( list ) ) ) {}

  /** 
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] head         the head record of the section
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
    try : LegendreCoefficients( ListRecord( it, end, lineNumber,
                                            MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while parsing Legendre coefficients" );
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
   *  @brief Return the Legendre order for the angular distribution (equal to
   *         the number of coefficients in the distribution)
   */
  int NL() const { return ListRecord::NPL(); }

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
