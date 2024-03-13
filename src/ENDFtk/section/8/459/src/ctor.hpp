//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Type() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] zaid      the material ZAID value
 *  @param[in] awr       the atomic weight ratio
 *  @param[in] yields    the fission yield data
 */
Type( int zaid, double awr, std::vector< FissionYieldData >&& yields ) :
  BaseWithoutMT( zaid, awr ),
  data_( std::move( yields ) ) {}

/**
 *  @brief Constructor for energy independent yields
 *
 *  @param[in] zaid           the material ZAID value
 *  @param[in] awr            the atomic weight ratio
 *  @param[in] identifiers    the fission product identifiers (NFP values)
 *  @param[in] states         the isomeric states (NFP values)
 *  @param[in] yields         the fission yield values and uncertainties
 *                            (NFP pairs)
 */
Type( int zaid, double awr,
      std::vector< unsigned int >&& identifiers,
      std::vector< unsigned int >&& states,
      std::vector< std::array< double, 2 > >&& yields )
  try : Type( zaid, awr,
              std::vector< FissionYieldData >{
                FissionYieldData( std::move( identifiers ), std::move( states ),
                                  std::move( yields ) ) } ) {}
  catch ( std::exception& e ) {

    Log::info( "Trouble while constructing section 459 of File 8" );
    throw;
  }

/**
 *  @brief Constructor for energy dependent yields where each energy has the
 *         same fission products
 *
 *  @param[in] zaid           the material ZAID value
 *  @param[in] awr            the atomic weight ratio
 *  @param[in] identifiers    the fission product identifiers (NFP values)
 *  @param[in] states         the isomeric states (NFP values)
 *  @param[in] energies       the incident neutron energies (NE values)
 *  @param[in] interpolants   the interpolation types (NE-1 values)
 *  @param[in] yields         the fission yield values and uncertainties
 *                            (NFP arrays of NE pairs)
 */
Type( int zaid, double awr,
      std::vector< unsigned int >&& identifiers,
      std::vector< unsigned int >&& states,
      std::vector< double >&& energies,
      std::vector< unsigned int >&& interpolants,
      std::vector< std::vector< std::array< double, 2 > > >&& yields )
  try : Type( zaid, awr,
              generateFissionYields( std::move( identifiers ),
                                     std::move( states ),
                                     std::move( energies ),
                                     std::move( interpolants ),
                                     std::move( yields ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Trouble while constructing section 459 of File 8" );
    throw;
  }

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
              readSequence< FissionYieldData >( begin, end, lineNumber,
                                                MAT, 8, 459, head.L1() ) ) {
    readSEND(begin, end, lineNumber, MAT, 8 );
  } catch ( std::exception& e ) {
    Log::info( "Trouble while reading section 459 of File 8 of Material {}",
               MAT );
    throw e;
  }
