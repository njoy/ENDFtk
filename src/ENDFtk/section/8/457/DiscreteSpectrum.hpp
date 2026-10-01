/**
 *  @class
 *  @brief Discrete spectrum information
 *
 *  The DiscreteSpectrum class is used to store spectral information for a
 *  single discrete energy from MF8/MT457.
 *
 *  All quantities are given as values with associated uncertainties so these
 *  are handled as arrays of size 2.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT DiscreteSpectrum : protected ListRecord {

  /* members */

  /* auxiliary functions */

  static void
  verifyNT( int NT ) {

    if ( ( NT != 4 ) && ( NT != 6 ) && ( NT != 8 ) && ( NT != 10 ) && ( NT != 12 ) ) {

      Log::error( "Encountered illegal NT value" );
      Log::info( "NT can only be equal to 4, 6, 8, 10 or 12" );
      Log::info( "NT value: {}", NT );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( double rtyp, double type,
                const std::array< double, 2 >& ri ) {

    return { rtyp, type, ri[0], ri[1] };
  }

  static std::vector< double >
  generateList( double rtyp, double type,
                const std::array< double, 2 >& ri,
                const std::array< double, 2 >& ris ) {

    return { rtyp, type, ri[0], ri[1], ris[0], ris[1] };
  }

  static std::vector< double >
  generateList( double rtyp, double type,
                const std::array< double, 2 >& ri,
                const std::array< double, 2 >& ris,
                const std::array< double, 2 >& ricc ) {

    return { rtyp, type, ri[0], ri[1], ris[0], ris[1],
             ricc[0], ricc[1] };
  }

  static std::vector< double >
  generateList( double rtyp, double type,
                const std::array< double, 2 >& ri,
                const std::array< double, 2 >& ris,
                const std::array< double, 2 >& ricc,
                const std::array< double, 2 >& rick,
                const std::array< double, 2 >& ricl ) {

    return { rtyp, type, ri[0], ri[1], ris[0], ris[1],
             ricc[0], ricc[1], rick[0], rick[1], ricl[0], ricl[1] };
  }

  std::array< double, 2 >
  returnArray( int index ) const {

    if ( this->NT() > index ) {

      return {{ ListRecord::list()[index], ListRecord::list()[index+1] }};
    }
    else {

      return {{ 0.0, 0.0 }};
    }
  }

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  The number of values in the list should be less than or equal to 12, this is
   *  checked.
   *
   *  @param[in] list   the ListRecord to be moved into the object
   */
  DiscreteSpectrum( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifyNT( this->NT() );
  }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] chain        the ENDF decay chain
   *  @param[in] energy       the energy and uncertainty
   *  @param[in] intensity    the relative intensity and uncertainty
   *  @param[in] type         the transition type
   */
  DiscreteSpectrum( double chain,
                    const std::array< double, 2 >& energy,
                    const std::array< double, 2 >& intensity,
                    double type ) :
    // this can never fail, try-catch would be unreachable
    DiscreteSpectrum(
          ListRecord( energy[0], energy[1], 0, 0, 0,
                      generateList( chain, type, intensity ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] chain        the ENDF decay chain
   *  @param[in] energy       the energy and uncertainty
   *  @param[in] intensity    the relative intensity and uncertainty
   *  @param[in] type         the transition type
   *  @param[in] ris          internal pair formation coefficient or
   *                          positron intensity
   */
  DiscreteSpectrum( double chain,
                    const std::array< double, 2 >& energy,
                    const std::array< double, 2 >& intensity,
                    double type,
                    const std::array< double, 2 >& ris ) :
    // this can never fail, try-catch would be unreachable
    DiscreteSpectrum(
          ListRecord( energy[0], energy[1], 0, 0, 0,
                      generateList( chain, type,
                                    intensity,
                                    ris ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] chain        the ENDF decay chain
   *  @param[in] energy       the energy and uncertainty
   *  @param[in] intensity    the relative intensity and uncertainty
   *  @param[in] type         the transition type
   *  @param[in] ris          internal pair formation coefficient or
   *                          positron intensity
   *  @param[in] ricc         the total internal conversion coefficient
   */
  DiscreteSpectrum( double chain,
                    const std::array< double, 2 >& energy,
                    const std::array< double, 2 >& intensity,
                    double type,
                    const std::array< double, 2 >& ris,
                    const std::array< double, 2 >& ricc ) :
    // this can never fail, try-catch would be unreachable
    DiscreteSpectrum(
          ListRecord( energy[0], energy[1], 0, 0, 0,
                      generateList( chain, type,
                                    intensity,
                                    ris, ricc ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] chain        the ENDF decay chain
   *  @param[in] energy       the energy and uncertainty
   *  @param[in] intensity    the relative intensity and uncertainty
   *  @param[in] type         the transition type
   *  @param[in] ris          internal pair formation coefficient or
   *                          positron intensity
   *  @param[in] ricc         the total internal conversion coefficient
   *  @param[in] rick         the K shell internal conversion coefficient
   *  @param[in] ricl         the L shell internal conversion coefficient
   */
  DiscreteSpectrum( double chain,
                    const std::array< double, 2 >& energy,
                    const std::array< double, 2 >& intensity,
                    double type,
                    const std::array< double, 2 >& ris,
                    const std::array< double, 2 >& ricc,
                    const std::array< double, 2 >& rick,
                    const std::array< double, 2 >& ricl ) :
    // this can never fail, try-catch would be unreachable
    DiscreteSpectrum(
          ListRecord( energy[0], energy[1], 0, 0, 0,
                      generateList( chain, type,
                                    intensity,
                                    ris, ricc, rick, ricl ) ) ) {}

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
  DiscreteSpectrum( Iterator& it, const Iterator& end, long& lineNumber,
                    int MAT, int MF, int MT )
    try : DiscreteSpectrum( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading discrete spectrum data" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the number of entries
   */
  int NT() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the decay chain responsible for this spectrum
   */
  double RTYP() const { return ListRecord::list()[0]; }

  /**
   *  @brief Return the decay chain responsible for this spectrum
   */
  double decayChain() const { return this->RTYP(); }

  /**
   *  @brief Return the discrete energy value and uncertainty
   */
  auto ER() const {

      return std::array< double, 2 >( {{ ListRecord::C1(),
                                         ListRecord::C2() }} );
  }

  /**
   *  @brief Return the discrete energy value and uncertainty
   */
  auto discreteEnergy() const { return this->ER(); }

  /**
   *  @brief Return the relative intensity and uncertainty
   */
  auto RI() const { return this->returnArray( 2 ); }

  /**
   *  @brief Return the relative intensity and uncertainty
   */
  auto relativeIntensity() const { return this->RI(); }

  /**
   *  @brief Transition type for beta and electron capture
   */
  double TYPE() const { return ListRecord::list()[1]; }

  /**
   *  @brief Transition type for beta and electron capture
   */
  double type() const { return this->TYPE(); }

  /**
   *  @brief Return the RIS value and its uncertainty, the internal pair
   *         formation coefficient (STYP=0.0) or the positron intensity
   *         (STYP=2.0)
   */
  auto RIS() const { return this->returnArray( 4 ); }

  /**
   *  @brief Return the RIS value and its uncertainty, the internal pair
   *         formation coefficient (STYP=0.0) or the positron intensity
   *         (STYP=2.0)
   */
  auto internalPairFormationCoefficient() const { return this->RIS(); }

  /**
   *  @brief Return the total internal conversion coefficient or RICC value and
   *         its uncertainty (STYP=0.0 only)
   */
  auto RICC() const { return this->returnArray( 6 ); }

  /**
   *  @brief Return the total internal conversion coefficient or RICC value and
   *         its uncertainty (STYP=0.0 only)
   */
  auto totalInternalConversionCoefficient() const { return this->RICC(); }

  /**
   *  @brief Return the K shell internal conversion coefficient or RICK value
   *         and its uncertainty (STYP=0.0 only)
   */
  auto RICK() const { return this->returnArray( 8 ); }

  /**
   *  @brief Return the K shell internal conversion coefficient or RICK value
   *         and its uncertainty (STYP=0.0 only)
   */
  auto internalConversionCoefficientKShell() const { return this->RICK(); }

  /**
   *  @brief Return the L shell internal conversion coefficient or RICL value
   *         and its uncertainty (STYP=0.0 only)
   */
  auto RICL() const { return this->returnArray( 10 ); }

  /**
   *  @brief Return the L shell internal conversion coefficient or RICL value
   *         and its uncertainty (STYP=0.0 only)
   */
  auto internalConversionCoefficientLShell() const { return this->RICL(); }

  using ListRecord::NC;
  using ListRecord::print;
};
