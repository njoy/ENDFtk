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

private:

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
