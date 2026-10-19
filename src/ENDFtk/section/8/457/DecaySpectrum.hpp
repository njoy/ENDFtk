/**
 *  @class
 *  @brief Spectrum information for a specific decay particle type
 *
 *  The DecaySpectrum class is used to store the decay spectrum for a single
 *  particle type from MF8/MT457.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT DecaySpectrum {

public:

  using OptionalContinuousSpectrum = std::optional< ContinuousSpectrum >;

private:

  ListRecord data_;
  std::vector< DiscreteSpectrum > discrete_;
  OptionalContinuousSpectrum continuous_;

  /* auxiliary functions */

  static void
  verifyLCOV( int LCOV ) {

    if ( LCOV != 0 ) {

      Log::error( "Encountered unsupported LCOV value: {}", LCOV );
      throw std::exception();
    }
  }

  static void
  verifyDiscreteSize( int LCON, int size ) {

    if ( LCON == 2 and size ==0 ) {

      Log::error( "Expected at least one discrete spectrum for LCON 2" );
      throw std::exception();
    }
  }

  template< typename Iterator >
  static std::optional< ContinuousSpectrum >
  readContinuous( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT,
                  int MF,
                  int MT,
                  int lcon ) {
    if ( lcon == 0 ) return std::nullopt;
    return std::make_optional( ContinuousSpectrum( begin, end, lineNumber,
                                                   MAT, MF, MT ) );
  }

  /* constructor */

  DecaySpectrum( ListRecord&& list,
                 std::vector< DiscreteSpectrum >&& spectra,
                 std::optional< ContinuousSpectrum >&& continuous ) :
    data_( std::move( list ) ), discrete_( std::move( spectra ) ),
    continuous_( std::move( continuous ) ) {

    verifyDiscreteSize( this->LCON(), this->discrete_.size() );
  }

  template< typename Iterator >
  DecaySpectrum( ListRecord&& list,
                 std::vector< DiscreteSpectrum >&& spectra,
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) :
    DecaySpectrum( std::move( list ),
                   std::move( spectra ),
                   readContinuous( it, end, lineNumber, MAT, MF, MT,
                                   list.L1() ) ) {

    verifyLCOV( this->LCOV() );
  }

  template< typename Iterator >
  DecaySpectrum( ListRecord&& list,
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) :
    DecaySpectrum( std::move( list ),
                   readSequence< DiscreteSpectrum >( it, end, lineNumber,
                                                     MAT, MF, MT, list.N2() ),
                   it, end, lineNumber, MAT, MF, MT ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor for discrete spectra only (LCON=0)
   *
   *  @param[in] type        the particle type for which data is given
   *  @param[in] dnorm       the spectra normalisation factor and its
   *                         uncertainty
   *  @param[in] energy      the average decay energy and its uncertainty
   *  @param[in] dspectra    the spectra spectra
   */
  DecaySpectrum( double type,
                 std::array< double, 2 > dnorm,
                 std::array< double, 2 > energy,
                 std::vector< DiscreteSpectrum >&& dspectra ) :
    // this can never fail, try-catch would be unreachable
    DecaySpectrum( ListRecord( 0.0, type, 0, 0, dspectra.size(),
                               { dnorm[0], dnorm[1], energy[0],
                                 energy[1], 0.0, 0.0 } ),
                   std::move( dspectra ),
                   std::nullopt ) {}

  /**
   *  @brief Constructor for continuous spectra only (LCON=1)
   *
   *  @param[in] type         the particle type for which spectral data is given
   *  @param[in] cnorm        the continuous normalisation factor and its uncertainty
   *  @param[in] energy       the average decay energy and its uncertainty
   *  @param[in] cspectrum    the continuous spectrum
   */
  DecaySpectrum( double type,
                 std::array< double, 2 > cnorm,
                 std::array< double, 2 > energy,
                 ContinuousSpectrum&& cspectrum ) :
    // this can never fail, try-catch would be unreachable
    DecaySpectrum( ListRecord( 0.0, type, 1, 0, 0,
                               { 0.0, 0.0,
                                 energy[0], energy[1],
                                 cnorm[0], cnorm[1] } ),
                   {},
                   std::make_optional( std::move( cspectrum ) ) ) {}

  /**
   *  @brief Constructor for discrete spectra and continuous spectrum (LCON=2)
   *
   *  @param[in] type         the particle type for which spectral data is given
   *  @param[in] dnorm        the spectra normalisation factor and its uncertainty
   *  @param[in] cnorm        the continuous normalisation factor and its uncertainty
   *  @param[in] energy       the average decay energy and its uncertainty
   *  @param[in] dspectra     the discrete spectra
   *  @param[in] cspectrum    the continuous spectrum
   */
  DecaySpectrum( double type,
                 std::array< double, 2 > dnorm,
                 std::array< double, 2 > cnorm,
                 std::array< double, 2 > energy,
                 std::vector< DiscreteSpectrum >&& dspectra,
                 ContinuousSpectrum&& cspectrum )
    try : DecaySpectrum( ListRecord( 0.0, type, 2, 0, dspectra.size(),
                                     { dnorm[0], dnorm[1],
                                       energy[0], energy[1],
                                       cnorm[0], cnorm[1] } ),
                         std::move( dspectra ),
                         std::make_optional( std::move( cspectrum ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing decay spectrum data "
                 "with LCON=2" );
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
  DecaySpectrum( Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT )
    try : DecaySpectrum( ListRecord( it, end, lineNumber, MAT, MF, MT ),
                         it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading decay spectrum data" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the radiation type STYP for which spectral data is given
   *         See ENDF102, section 8.4c for more information.
   */
  double STYP() const { return this->data_.C2(); }

  /**
   *  @brief Return the radiation type STYP for which spectral data is given
   *         See ENDF102, section 8.4c for more information.
   */
  double radiationType() const { return this->STYP(); }

  /**
   *  @brief Return the spectral type flag
   */
  int LCON() const { return this->data_.L1(); }

  /**
   *  @brief Return the spectral type flag
   */
  int spectralTypeFlag() const { return this->LCON(); }

  /**
   *  @brief Return the covariance data flag
   */
  int LCOV() const { return this->data_.L2(); }

  /**
   *  @brief Return the covariance data flag
   */
  int covarianceFlag() const { return this->LCOV(); }

  /**
   *  @brief Return the number of discrete decay spectra
   */
  int NER() const { return this->data_.N2(); }

  /**
   *  @brief Return the number of discrete decay spectra
   */
  int numberDiscreteSpectra() const { return this->NER(); }

  /**
   *  @brief Return the discrete normalisation factor and its uncertainty
   */
  auto FD() const {

    return std::array< double, 2 >( {{ this->data_.list()[0],
                                       this->data_.list()[1] }} );
  }

  /**
   *  @brief Return the discrete normalisation factor and its uncertainty
   */
  auto discreteNormalisationFactor() const { return this->FD(); }

  /**
   *  @brief Return the continuous normalisation factor and its uncertainty
   */
  auto FC() const {

    return std::array< double, 2 >( {{ this->data_.list()[4],
                                       this->data_.list()[5] }} );
  }

  /**
   *  @brief Return the continuous normalisation factor and its uncertainty
   */
  auto continuousNormalisationFactor() const { return this->FC(); }

  /**
   *  @brief Return the average decay energy and its uncertainty
   */
  auto ERAV() const {

    return std::array< double, 2 >( {{ this->data_.list()[2],
                                       this->data_.list()[3] }} );
  }

  /**
   *  @brief Return the average decay energy and its uncertainty
   */
  auto averageDecayEnergy() const { return this->ERAV(); }

  /**
   *  @brief Return the discrete spectra, if any are defined
   */
  auto discreteSpectra() const {

    using namespace njoy::tools;
    return std20::views::all( this->discrete_ );
  }

  /**
   *  @brief Return the continuous spectrum, if it is defined
   */
  const OptionalContinuousSpectrum& continuousSpectrum() const {

    return this->continuous_;
  }

  /**
   *  @brief Return the number of lines in this MF8/MT457 section
   */
  long NC() const {
    long NC = this->data_.NC();
    for ( const auto& entry : this->discrete_ ) NC += entry.NC();
    if ( this->continuous_ ) NC += this->continuous_->NC();
    return NC;
  };

  /**
   *  @brief Print the MF8/MT457 section (includes SEND record)
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
    this->data_.print( it, MAT, MF, MT );
    for ( const auto& entry : this->discrete_ ) entry.print( it, MAT, MF, MT );
    if ( this->continuous_ ) this->continuous_->print( it, MAT, MF, MT );
  }
};
