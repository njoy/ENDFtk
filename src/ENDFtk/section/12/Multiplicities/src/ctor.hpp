private:

/**
 *  @brief Private constructor
 */
Multiplicities( std::optional< TotalMultiplicity >&& total,
                std::vector< PartialMultiplicity >&& partials ) :
  total_( std::move( total ) ), partials_( std::move( partials ) ) {

  verifyNK( this->NK() );
}

public:
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

private:

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
