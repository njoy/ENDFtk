//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
Type() = default;
#endif

/**
 *  @brief Constructor for isotropic photon distributions
 *
 *  @param[in] mt              the MT number for the section
 *  @param[in] zaid            the material ZAID value
 *  @param[in] awr             the atomic weight ratio
 *  @param[in] nk              the number of photons
 */
Type( int MT, int zaid, double awr, unsigned int nk ) :
  Base( zaid, awr, MT ),
  nk_( nk ), photons_() {}

/**
 *  @brief Constructor
 *
 *  @param[in] mt        the MT number for the section
 *  @param[in] zaid      the material ZAID value
 *  @param[in] awr       the atomic weight ratio
 *  @param[in] photons   the photon distribution data
 */
Type( int MT, int zaid, double awr,
      std::vector< PhotonDistribution >&& photons ) :
  Base( zaid, awr, MT ),
  nk_(0), photons_( std::move( photons ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] mt            the MT number for the section
 *  @param[in] zaid          the material ZAID value
 *  @param[in] isotropic     the photon and level energies for the isotropic
 *                           photons
 *  @param[in] anisotropic   the distribution data for the anisotropic photons
 */
Type( int MT, int zaid, double awr,
      std::vector< std::array< double, 2 > >&& isotropic,
      std::vector< AnisotropicPhotonDistribution >&& anisotropic ) :
  Type( MT, zaid, awr,
        makePhotonDistributions( std::move( isotropic ),
                                 std::move( anisotropic ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] mt            the MT number for the section
 *  @param[in] zaid          the material ZAID value
 *  @param[in] energies      the photon energy for each isotropic photon
 *  @param[in] levels        the level energy for each isotropic photon
 *  @param[in] anisotropic   the distribution data for the anisotropic photons
 */
 Type( int MT, int zaid, double awr,
       std::vector< double >&& energies,
       std::vector< double >&& levels,
       std::vector< AnisotropicPhotonDistribution >&& anisotropic ) :
   Type( MT, zaid, awr,
         makeArrays( std::move( energies ), std::move( levels ) ),
         std::move( anisotropic ) ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
Type( int MT, int zaid, double awr, unsigned int nk,
      std::vector< PhotonDistribution >&& photons ) :
  Base( zaid, awr, MT ),
  nk_( nk ), photons_( std::move( photons ) ) {}

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
Type ( HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try: Type( head.MT(), head.ZA(), head.AWR(), head.N1(),
             readPhotons( begin, end, lineNumber, head.MAT(), 14, head.MT(),
                          head.L1(), head.N2(), head.N1(), head.L2() ) ) {

    readSEND(begin, end, lineNumber, MAT, 14 );
  } catch( std::exception& e ) {

    Log::info
    ( "Encountered error while reading section {} of file 14 of material {}",
      head.MT(), MAT );
    throw;
  }
