private:

DecaySpectrum( ListRecord&& list,
               std::optional< std::vector< DiscreteSpectrum > >&& discrete,
               std::optional< ContinuousSpectrum >&& continuous ) :
  data_( std::move( list ) ), discrete_( std::move( discrete ) ),
  continuous_( std::move( continuous ) ) {}

public:
/** 
 *  @brief Constructor for discrete spectra only (LCON=0)
 *
 *  @param[in] styp          the particle type for which spectral data is given
 *  @param[in] fd            the discrete normalisation factor and its uncertainty
 *  @param[in] erav          the average decay energy and its uncertainty
 *  @param[in] discrete      the discrete spectra
 */
DecaySpectrum( double styp,
               std::array< double, 2 > fd,
               std::array< double, 2 > erav,
               std::vector< DiscreteSpectrum >&& discrete )
  try : DecaySpectrum( ListRecord( 0.0, styp, 0, 0, discrete.size(),
                                   { fd[0], fd[1],
                                     erav[0], erav[1],
                                     0.0, 0.0 } ),
                       std::make_optional( std::move( discrete ) ),
                       std::nullopt ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing decay spectrum data "
               "with LCON=0" );
    throw;
  }

/** 
 *  @brief Constructor for continuous spectra only (LCON=1)
 *
 *  @param[in] styp         the particle type for which spectral data is given
 *  @param[in] fc           the continuous normalisation factor and its uncertainty
 *  @param[in] erav         the average decay energy and its uncertainty
 *  @param[in] continuous   the continuous spectrum
 */
DecaySpectrum( double styp,
               std::array< double, 2 > fc,
               std::array< double, 2 > erav,
               ContinuousSpectrum&& continuous )
  try : DecaySpectrum( ListRecord( 0.0, styp, 1, 0, 0,
                                   { 0.0, 0.0,
                                     erav[0], erav[1],
                                     fc[0], fc[1] } ),
                       std::nullopt,
                       std::make_optional( std::move( continuous ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing decay spectrum data "
               "with LCON=1" );
    throw;
  }

/** 
 *  @brief Constructor for discrete and continuous spectra (LCON=2)
 *
 *  @param[in] styp         the particle type for which spectral data is given
 *  @param[in] fd           the discrete normalisation factor and its uncertainty
 *  @param[in] fc           the continuous normalisation factor and its uncertainty
 *  @param[in] erav         the average decay energy and its uncertainty
 *  @param[in] continuous   the continuous spectrum
 */
DecaySpectrum( double styp,
               std::array< double, 2 > fd,
               std::array< double, 2 > fc,
               std::array< double, 2 > erav,
               std::vector< DiscreteSpectrum >&& discrete,
               ContinuousSpectrum&& continuous )
  try : DecaySpectrum( ListRecord( 0.0, styp, 2, 0, discrete.size(),
                                   { fd[0], fd[1],
                                     erav[0], erav[1],
                                     fc[0], fc[1] } ),
                       std::make_optional( std::move( discrete ) ),
                       std::make_optional( std::move( continuous ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing decay spectrum data "
               "with LCON=2" );
    throw;
  }

private:

template< typename Iterator >
DecaySpectrum( ListRecord&& list,
               std::optional< std::vector< DiscreteSpectrum > >&& discrete,
               Iterator& it, const Iterator& end, long& lineNumber,
               int MAT, int MF, int MT ) :
  DecaySpectrum( std::move( list ),
                 std::move( discrete ),
                 readContinuous( it, end, lineNumber, MAT, MF, MT,
                                 list.L1() ) ) {

  verifyLCOV( this->LCOV() );
}

template< typename Iterator >
DecaySpectrum( ListRecord&& list,
               Iterator& it, const Iterator& end, long& lineNumber,
               int MAT, int MF, int MT ) :
  DecaySpectrum( std::move( list ),
                 readDiscrete( it, end, lineNumber, MAT, MF, MT,
                               list.L1(), list.N2() ),
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
