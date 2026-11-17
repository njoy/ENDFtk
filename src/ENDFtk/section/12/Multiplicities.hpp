/**
 *  @class
 *  @brief The energy dependence of the photon production cross section
 *         is given as multiplicities
 *
 *  The Multiplicities class is used to represent the case in which
 *  the energy dependence of the photon production cross sections is given
 *  as multiplicities. The data consists of a range of partial multiplicities
 *  and an optional total multiplicity (if there is more than 1 partial).
 *
 *  See ENDF102, section 12.2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT Multiplicities {

public:

  /* type aliases */

  using OptionalTotalMultiplicity = std::optional< TotalMultiplicity >;

private:

  /* fields */

  std::optional< TotalMultiplicity > total_;
  std::vector< PartialMultiplicity > partials_;

  /* auxiliary functions */

  static void
  verifyNK( int NK ) {

    if ( NK <= 0 ) {

      Log::error( "Encountered illegal NK value" );
      Log::info( "NK must be larger than 0" );
      Log::info( "NK value: {}", NK );
      throw std::exception();
    }
  }

  template< typename Iterator >
  static std::optional< TotalMultiplicity >
  readTotalMultiplicity( Iterator& begin,
                         const Iterator& end,
                         long& lineNumber,
                         int MAT,
                         int MF,
                         int MT,
                         int size ) {

    if ( size == 1 ) {

      return std::nullopt;
    }

    return std::make_optional( TotalMultiplicity( begin, end, lineNumber,
                                                  MAT, MF, MT ) );
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  Multiplicities( std::optional< TotalMultiplicity >&& total,
                  std::vector< PartialMultiplicity >&& partials ) :
    total_( std::move( total ) ), partials_( std::move( partials ) ) {

    verifyNK( this->NK() );
  }

  /**
   *  @brief Private constructor
   */
  template< typename Iterator >
  Multiplicities( std::optional< TotalMultiplicity >&& total,
                  Iterator& begin, const Iterator& end,
                  long& lineNumber, int MAT, int MF, int MT,
                  int NK ) :
    Multiplicities( std::move( total ),
                    readSequence< PartialMultiplicity >( begin, end, lineNumber,
                                                         MAT, MF, MT, NK ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  Multiplicities() = default;
  #endif

  /**
   *  @brief Constructor (only one partial given, no total required)
   *
   *  @param[in] partial   the partial multiplicity
   */
  Multiplicities( PartialMultiplicity&& partial ) :
    Multiplicities( std::nullopt, { std::move( partial ) } ) {}

  /**
   *  @brief Constructor (one total and multiple partials)
   *
   *  @param[in] total      the total multiplicity
   *  @param[in] partials   the partial multiplicities
   */
  Multiplicities( TotalMultiplicity&& total,
                  std::vector< PartialMultiplicity >&& partials ) :
    Multiplicities( std::make_optional( std::move( total ) ),
                    std::move( partials ) ) {}

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
   *  @param[in] NK           the number of partials
   */
  template< typename Iterator >
  Multiplicities( Iterator& begin, const Iterator& end,
                  long& lineNumber, int MAT, int MF, int MT,
                  int NK )
    try : Multiplicities( readTotalMultiplicity( begin, end, lineNumber,
                                                 MAT, MF, MT, NK ),
                          begin, end, lineNumber, MAT, MF, MT, NK ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing photon multiplicities" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the photon production representation type
   */
  static constexpr int LO() { return 1; }

  /**
   *  @brief Return the photon production representation type
   */
  int representation() const { return this->LO(); }

  /**
   *  @brief Return the number of photons (discrete and continuum) with
   *         partial multiplicities
   */
  int NK() const { return this->partials_.size(); }

  /**
   *  @brief Return the number of photons (discrete and continuum) with
   *         partial multiplicities
   */
  int numberPhotons() const { return this->NK(); }

  /**
   *  @brief Return the total multiplicity (optional)
   */
  const OptionalTotalMultiplicity& totalMultiplicity() const {

    return this->total_;
  }

  /**
   *  @brief Return the partial multiplicities
   */
  auto photonPartialMultiplicities() const {

    using namespace njoy::tools;
    return this->partials_ | std20::views::all;
  }

  /**
   *  @brief Return the number of lines in this MF12 component
   */
  long NC() const {
    long NC = 0;
    if ( this->total_ ) { NC += this->total_->NC(); }
    for ( const auto& entry : this->partials_ ) {

      NC += entry.NC();
    }
    return NC;
  }

  /**
   *  @brief Print this MF12 component
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

    if ( this->total_ ) { this->total_->print( it, MAT, MF, MT ); }
    for ( const auto& entry : this->partials_ ) {

      entry.print( it, MAT, MF, MT );
    }
  }
};
