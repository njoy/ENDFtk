private:

/**
 *  @brief Private constructor
 */
TabulatedComponents(
    int nfc,
    ThermalPointComponents&& thermal,
    std::array< std::optional< EnergyReleaseComponent >, 9 >&& components ) :
  nfc_( nfc ), values_( std::move( thermal ) ),
  components_( std::move( components ) ) {}

public:

/**
 *  @brief Constructor
 *
 *  @param[in] thermal    the thermal point evaluation of the energy release
 *  @param[in] tables     the tabulated components
 */
TabulatedComponents( ThermalPointComponents&& thermal,
                     std::vector< EnergyReleaseComponent >&& tables )
  try : TabulatedComponents( tables.size(), std::move( thermal ),
                             generateTables( std::move( tables ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a tabulated evaluation" );
    throw;
  }

private:

/**
 *  @brief Private constructor
 */
template< typename Iterator >
TabulatedComponents( int NFC,
                     ThermalPointComponents&& thermal,
                     Iterator& begin,
                     const Iterator& end,
                     long& lineNumber,
                     int MAT,
                     int MF,
                     int MT ) :
  TabulatedComponents(
      NFC, std::move( thermal ),
      readTables( begin, end, lineNumber, MAT, MF, MT, NFC ) ) {}

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
TabulatedComponents( Iterator& begin,
                     const Iterator& end,
                     long& lineNumber,
                     int MAT,
                     int MF,
                     int MT,
                     int NFC )
  try : TabulatedComponents(
            NFC,
            ThermalPointComponents( begin, end, lineNumber, MAT, MF, MT ),
            begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing a tabulated evaluation" );
    throw;
  }
