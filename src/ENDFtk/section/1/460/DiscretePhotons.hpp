/**
 *  @class
 *  @brief A collection of discrete photon multiplicities
 *
 *  See ENDF102, section 1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT DiscretePhotons {

  /* fields */

  std::vector< DiscretePhotonMultiplicity > photons_;

  /* auxiliary functions */

  static void
  verifySize( int NG ) {

    if ( NG <= 0 ) {

      Log::error( "Inconsistent data size" );
      Log::info( "Expected NG > 0" );
      Log::info( "NG value: {}", NG );
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
  DiscretePhotons() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] photons     the discrete photon data
   */
  DiscretePhotons( std::vector< DiscretePhotonMultiplicity >&& multiplicities )
    try : photons_( std::move( multiplicities ) ) {

      verifySize( this->NG() );
    }
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing discrete photon data" );
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
  DiscretePhotons( Iterator& begin,
                   const Iterator& end,
                   long& lineNumber,
                   int MAT,
                   int MF,
                   int MT,
                   int NG )
    try : DiscretePhotons(
              readSequence< DiscretePhotonMultiplicity >( begin, end, lineNumber,
                                                          MAT, MF, MT, NG ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing discrete photon data" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the representation type for the delayed photon data
   */
  static constexpr int LO() { return 1; }

  /**
   *  @brief Return the representation type for the delayed photon data
   */
  int representation() const { return this->LO(); }

  /**
   *  @brief Return the number of discrete photons
   */
  int NG() const { return this->photons_.size(); }

  /**
   *  @brief Return the number of discrete photons
   */
  int numberDiscretePhotons() const { return this->NG(); }

  /**
   *  @brief Return the discrete photon data
   */
  auto photons() const {

    using namespace njoy::tools;
    return std20::views::all( this->photons_ );
  }

  /**
   *  @brief Return the number of lines in this MF1/MT458 section
   */
  long NC() const {

    long NC = 0;
    for ( auto& entry : this->photons_ ) { NC += entry.NC(); }
    return NC;
  }

  /**
   *  @brief Print the MF1/MT458 section (includes SEND record)
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

    for ( auto& entry : this->photons_ ) { entry.print( it, MAT, MF, MT ); }
  }
};
