/**
 *  @class
 *  @brief R-matrix limited spin group with resonance parameter uncertainties
 *
 *  The ResonanceChannels class here is very similar to the MF2 MT151 version
 *  but it does not have the background matrix elements.
 *
 *  See ENDF102, section 32.2.3.3 for more information - if you don't value
 *  your sanity.
 */
class ENDFTK_PYTHON_EXPORT SpinGroup  {

  /* fields */

  ResonanceChannels channels_;
  ResonanceParameters parameters_;

  /* auxiliary functions */

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  SpinGroup( ResonanceChannels&& channels,
             Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT ) :
    SpinGroup( std::move( channels ),
               ResonanceParameters( it, end, lineNumber, MAT, MF, MT ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  SpinGroup() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] channels      the resonance channel information
   *  @param[in] parameters    the associated resonance parameters
   */
  SpinGroup( ResonanceChannels&& channels, ResonanceParameters&& parameters ) :
    channels_( std::move( channels ) ),
    parameters_( std::move( parameters ) ) {}

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
   *  @brief Return the number of resonances
   */
  auto NRSA() const { return this->parameters_.NRSA(); }

  /**
   *  @brief Return the number of resonances
   */
  auto numberResonances() const { return this->NRSA(); }

  /**
   *  @brief Return the channel information
   */
  const ResonanceChannels& channels() const { return this->channels_; }

  /**
   *  @brief Return the resonance parameters for this spin group
   */
  const ResonanceParameters& parameters() const { return this->parameters_; }

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const { return this->channels_.NC() + this->parameters_.NC(); };

  /**
   *  @brief Print this MF32 MT151 component
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
  }
};
