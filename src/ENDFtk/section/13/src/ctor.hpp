private:

/**
 *  @brief Private constructor
 */
Type( int MT, int zaid, double awr,
      std::optional< TotalCrossSection >&& total,
      std::vector< PartialCrossSection >&& partials ) :
  Base( zaid, awr, MT ),
  total_( std::move( total ) ),
  partials_( std::move( partials ) ) {

  verifyNK( this->NK() );
}

public:

//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Type() = default;
#endif

/**
 *  @brief Constructor (only one partial given, no total required)
 *
 *  @param[in] partial   the partial cross section
 */
Type( int MT, int zaid, double awr,
      PartialCrossSection&& partial )
  try : Type( MT, zaid, awr, std::nullopt, { std::move( partial ) } ) {}
  catch ( std::exception& e ) {
   Log::info( "Trouble while constructing section {} of File 13", MT );
   throw e;
 }

/**
 *  @brief Constructor (one total and multiple partials)
 *
 *  @param[in] total      the total photon production cross section
 *  @param[in] partials   the partial photon production cross sections
 */
Type( int MT, int zaid, double awr,
      TotalCrossSection&& total,
      std::vector< PartialCrossSection >&& partials ) :
  Type( MT, zaid, awr,
        std::make_optional( std::move( total ) ),
        std::move( partials ) ) {}

private:

/**
 *  @brief Private constructor
 */
template< typename Iterator >
Type( int zaid, double awr,
      std::optional< TotalCrossSection >&& total,
      Iterator& begin, const Iterator& end,
      long& lineNumber, int MAT, int MF, int MT, int NK ) :
  Type( MT, zaid, awr,
        std::move( total ),
        readSequence< PartialCrossSection >( begin, end, lineNumber,
                                             MAT, MF, MT, NK ) ) {}

public:

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] head         the head record of the section
 *  @param[in] it           the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 */
template< typename Iterator >
Type( HEAD& head,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT )
  try : Type( head.ZA(), head.AWR(),
              readTotalCrossSection( begin, end, lineNumber,
                                     MAT, 13, head.MT(), head.N1() ),
              begin, end, lineNumber, MAT, 13, head.MT(), head.N1() ) {
    readSEND( begin, end, lineNumber, MAT, 13 );
  } catch ( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 13 of Material {}",
               head.MT(), MAT );
    throw e;
  }
