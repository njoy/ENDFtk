private:

/**
 *  @brief Private constructor
 */
Type( int zaid, double awr, int lrp, int lfi, int nlib, int nmod,
      std::array< ControlRecord, 3 >&& parameters,
      std::vector< TextRecord >&& description,
      std::vector< DirectoryRecord >&& index ) :
  BaseWithoutMT( zaid, awr ), lrp_( lrp ), lfi_( lfi ), nlib_( nlib ), nmod_( nmod ),
  parameters_( std::move( parameters ) ),
  description_( std::move( description ) ),
  index_( std::move( index ) ) {}

public:

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
 *  @param[in] zaid          the ZA value of the material
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] lrp           the resonance parameter flag
 *  @param[in] lfi           the fissile flag
 *  @param[in] nlib          the library type
 *  @param[in] nmod          the modification number
 *  @param[in] elis          the excitation energy
 *  @param[in] sta           the stability flag (whether or not the nuclide is unstable)
 *  @param[in] lis           the excited level number
 *  @param[in] liso          the isomeric state number
 *  @param[in] nfor          the library format version number
 *  @param[in] awi           the atomic weight ratio of the incident particle
 *  @param[in] emax          the maximum incident energy
 *  @param[in] lrel          the release number
 *  @param[in] nsub          the sublibrary number
 *  @param[in] nver          the version number
 *  @param[in] temp          the temperature
 *  @param[in] ldrv          the derived material flag
 *  @param[in] description   the descriptive information
 *  @param[in] index         the index
 *  @param[in] rtol          the reconstruction tolerance (internal NJOY value)
 */
Type( int zaid, double awr, int lrp, int lfi, int nlib, int nmod,
      double elis, double sta, int lis, int liso, int nfor,
      double awi, double emax, int lrel, int nsub, int nver,
      double temp, int ldrv,
      const std::string& description,
      std::vector< DirectoryRecord >&& index,
      double rtol = 0. ) :
  BaseWithoutMT( zaid, awr ), lrp_( lrp ), lfi_( lfi ), nlib_( nlib ), nmod_( nmod ),
  parameters_( makeParameters( elis, sta, lis, liso, nfor,
                               awi, emax, lrel, nsub, nver,
                               temp, rtol, ldrv,
                               ranges::cpp20::distance(
                                   ranges::cpp20::views::split( description, '\n' ) ),
                               index.size() ) ),
  description_( makeDescription( description ) ),
  index_( std::move( index ) ) {}

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] head         the head record of the section
 *  @param[in] begin        the current position in the buffer
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
  try :

    BaseWithoutMT( head, MAT, 1 ), lrp_( head.L1() ), lfi_( head.L2() ),
    nlib_( head.N1() ), nmod_( head.N2() ),
    parameters_( readParameters( begin, end, lineNumber, MAT ) ),
    description_( readSequence< TextRecord >(
                      begin, end, lineNumber, MAT, 1, 451,
                      this->parameters_[2].N1() ) ),
    index_( readSequence< DirectoryRecord >(
                begin, end, lineNumber, MAT, 1, 451,
                this->parameters_[2].N2() ) ) {
    readSEND(begin, end, lineNumber, MAT, 1 );
  }
  catch( std::exception& e ) {

    Log::info( "Trouble while reading section 451 of File 1 of Material {}",
               MAT );
    Log::info( "lineNumber: {}", lineNumber );
    throw e;
  }
