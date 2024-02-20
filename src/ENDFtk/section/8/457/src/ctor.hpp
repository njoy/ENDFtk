//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Type() = default;
#endif

/**
 *  @brief Constructor for stable nuclides only
 *
 *  @param[in] zaid       the material ZAID value
 *  @param[in] awr        the atomic weight ratio
 *  @param[in] lis        the excited level number
 *  @param[in] liso       the isomeric state number
 *  @param[in] spin       the nuclide spin
 *  @param[in] parity     the nuclide parity
 */
Type( int zaid, double awr, int lis, int liso, double spin, double parity ) :
  BaseWithoutMT( zaid, awr ),
  lis_( lis ), liso_( liso ), nst_( true ),
  energies_(), modes_(spin, parity), spectra_() {}

/**
 *  @brief Constructor
 *
 *  @param[in] zaid       the material ZAID value
 *  @param[in] awr        the atomic weight ratio
 *  @param[in] lis        the excited level number
 *  @param[in] liso       the isomeric state number
 *  @param[in] energies   the average decay energies
 *  @param[in] modes      the decay modes
 *  @param[in] spectra    the decay spectra
 */
Type( int zaid, double awr, int lis, int liso,
      AverageDecayEnergies&& energies,
      DecayModes&& modes,
      std::vector< DecaySpectrum >&& spectra ) :
  BaseWithoutMT( zaid, awr ),
  lis_( lis ), liso_( liso ), nst_( modes.NDK() == 0 ),
  energies_( std::move( energies ) ),
  modes_( std::move( modes ) ),
  spectra_( std::move( spectra ) ) {}

private:

template< typename Iterator >
Type( double za, double awr, int lis, int liso, int NSP,
      AverageDecayEnergies&& energies,
      DecayModes&& modes,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT ) :
  Type( za, awr, lis, liso,
        std::move( energies ),
        std::move( modes ),
        readSequence< DecaySpectrum >( begin, end, lineNumber,
                                       MAT, 8, 457, NSP ) ) {}

template< typename Iterator >
Type( double za, double awr, int lis, int liso, int NSP,
      AverageDecayEnergies&& energies,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT ) :
  Type( za, awr, lis, liso, NSP,
        std::move( energies ),
        DecayModes( begin, end, lineNumber, MAT, 8, 457 ),
        begin, end, lineNumber, MAT ) {}

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
  try : Type( head.ZA(), head.AWR(), head.L1(), head.L2(), head.N2(),
              AverageDecayEnergies( begin, end, lineNumber, MAT, 8, 457 ),
              begin, end, lineNumber, MAT ) {
    readSEND(begin, end, lineNumber, MAT, 8 );
  } catch ( std::exception& e ) {
    Log::info( "Trouble while reading section 457 of File 8 of Material {}",
               MAT );
    throw e;
  }
