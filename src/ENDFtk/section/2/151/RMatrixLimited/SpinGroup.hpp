/**
 *  @class
 *  @brief R-matrix limited spin group with resonance parameters
 *
 *  The SpinGroup class is used to represent a spin group in the R-matrix
 *  limited resonance parameters from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT SpinGroup  {

  /* fields */

  ResonanceChannels channels_;
  ResonanceParameters parameters_;
  BackgroundChannels background_;

  /* auxiliary functions */

  static void
  verify( int KBK1, int KBK2, int NCH1, int NCH2 ) {

    if ( KBK1 != KBK2 ) {

      Log::error( "KBK is not consistent with the number of channels with a "
                  "background R-matrix value" );
      Log::info( "KBK value: {}", KBK1 );
      Log::info( "Channels with a background R-matrix value: {}", KBK2 );
      throw std::exception();
    }

    if ( NCH1 != NCH2 ) {

      Log::error( "NCH is not consistent with the background R-matrix data" );
      Log::info( "NCH value: {}", NCH1 );
      Log::info( "Number of channels from background R-matrices: {}", NCH2 );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  SpinGroup( ResonanceChannels&& channels,
             ResonanceParameters&& parameters,
             Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT, int NCH, int KBK ) :
    SpinGroup( std::move( channels ), std::move( parameters ),
               BackgroundChannels( it, end, lineNumber,
                                   MAT, MF, MT, NCH, KBK ) ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  SpinGroup( ResonanceChannels&& channels,
             Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT ) :
    SpinGroup( std::move( channels ),
               ResonanceParameters( it, end, lineNumber, MAT, MF, MT ),
               it, end, lineNumber, MAT, MF, MT,
               channels.NCH(), channels.KBK() ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] channels      the resonance channel information
   *  @param[in] parameters    the associated resonance parameters
   *  @param[in] background    the background R-matrices
   */
  SpinGroup( ResonanceChannels&& channels, ResonanceParameters&& parameters,
             BackgroundChannels&& background ) :
    channels_( std::move( channels ) ),
    parameters_( std::move( parameters ) ),
    background_( std::move( background ) ) {

      verify( this->channels_.KBK(), this->background_.KBK(),
              this->channels_.NCH(), this->background_.NCH() );
    }

  /**
   *  @brief Constructor
   *
   *  @param[in] channels     the resonance channel information
   *  @param[in] parameters   the associated resonance parameters
   */
  SpinGroup( ResonanceChannels&& channels, ResonanceParameters&& parameters )
    try : SpinGroup( std::move( channels ), std::move( parameters ),
                     BackgroundChannels( channels.NCH(), {} ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a spin group" );
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
  SpinGroup( Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT )
    try: SpinGroup( ResonanceChannels( it, end, lineNumber, MAT, MF, MT ),
                    it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a spin group" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the spin for this spin group
   */
  double AJ() const { return this->channels_.AJ(); }

  /**
   *  @brief Return the spin for this spin group
   */
  double spin() const { return this->AJ(); }

  /**
   *  @brief Return the parity for this spin group
   */
  double PJ() const { return this->channels_.PJ(); }

  /**
   *  @brief Return the parity for this spin group
   */
  double parity() const { return this->PJ(); }

  /**
   *  @brief Return the number of channels
   */
  auto NCH() const { return this->channels_.NCH(); }

  /**
   *  @brief Return the number of channels
   */
  auto numberChannels() const { return this->NCH(); }

  /**
   *  @brief Return the number of channels with background R-matrix values
   */
  auto KBK() const { return this->channels_.KBK(); }

  /**
   *  @brief Return the number of channels with background R-matrix values
   */
  auto numberBackgroundChannels() const { return this->NCH(); }

  /**
   *  @brief Return the number of resonances
   */
  auto NRS() const { return this->parameters_.NRS(); }

  /**
   *  @brief Return the number of resonances
   */
  auto numberResonances() const { return this->NRS(); }

  /**
   *  @brief Return the channel information
   */
  const ResonanceChannels& channels() const { return this->channels_; }

  /**
   *  @brief Return the resonance parameters for this spin group
   */
  const ResonanceParameters& parameters() const { return this->parameters_; }

  /**
   *  @brief Return the background R-matrix values for the spin group channels
   */
  const BackgroundChannels& background() const { return this->background_; }

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const { return this->channels_.NC() + this->parameters_.NC() +
                           this->background_.NC(); };

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

    this->channels_.print( it, MAT, MF, MT );
    this->parameters_.print( it, MAT, MF, MT );
    this->background_.print( it, MAT, MF, MT );
  }
};
