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
 *  @param[in] zaid       the material ZAID value
 *  @param[in] awr        the atomic weight ratio
 *  @param[in] isotopes   the isotopes for the section
 */
Type( double zaid, double awr, std::vector< Isotope >&& isotopes ) :
  BaseWithoutMT( zaid, awr ), isotopes_( std::move( isotopes ) ) {

    verifyNIS( this->NIS() );
  }

/**
 *  @brief Constructor for a single isotope
 *
 *  @param[in] zaid     the material ZAID value
 *  @param[in] awr      the atomic weight ratio
 *  @param[in] lfw      the lfw flag for unresolved resonances
 *  @param[in] ranges   the resonance ranges defined for the isotope
 */
Type( double zaid, double awr, bool lfw,
      std::vector< ResonanceRange >&& ranges ) :
  Type( zaid, awr,
        std::vector< Isotope >{ Isotope( zaid, 1., lfw,
                                std::move( ranges ) ) } ) {}

/**
 *  @brief Special case constructor (only scattering radius is given)
 *
 *  @param[in] zaid   the material ZAID value
 *  @param[in] awr    the atomic weight ratio
 *  @param[in] el     the lower limit of the resonance range
 *  @param[in] eh     the upper limit of the resonance range
 *  @param[in] spin   the spin of the target nucleus
 *  @param[in] ap     the scattering radius (in units of 10^-12 cm)
 */
Type( double zaid, double awr, double el, double eh, double spin, double ap ) :
  Type( zaid, awr,
        { { zaid, 1.0, 0,
            { { el, eh, 0, SpecialCase( spin, ap ), std::nullopt } } } } ) {}

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
Type ( const HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try:
    Type( head.ZA(), head.AWR(),
          readSequence< Isotope >( begin, end, lineNumber,
                                   MAT, 2, 151, head.N1() ) ) {

      readSEND( begin, end, lineNumber, MAT, 2 );
  } catch( std::exception& e ){
    Log::info( "Trouble while reading section 151 of File 2 of Material {}",
               MAT );
    throw e;
  }
