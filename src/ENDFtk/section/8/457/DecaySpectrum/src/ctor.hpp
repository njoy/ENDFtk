private:

DecaySpectrum( ListRecord&& list,
               std::vector< DiscreteSpectrum >&& spectra,
               std::optional< ContinuousSpectrum >&& continuous ) :
  data_( std::move( list ) ), discrete_( std::move( spectra ) ),
  continuous_( std::move( continuous ) ) {

  verifyDiscreteSize( this->LCON(), this->discrete_.size() );
}

public:
/**
 *  @brief Constructor for spectra spectra only (LCON=0)
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

private:

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
