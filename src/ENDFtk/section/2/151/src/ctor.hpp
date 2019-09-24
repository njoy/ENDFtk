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
  BaseWithoutMT( zaid, awr ),
  isotopes( 1,
            { zaid, 1.0, 0,
              { 1, resonanceParameters::SpecialCase( el, eh, spin, ap ) } } ) {}

template< typename Iterator >
Type ( const HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try:
    BaseWithoutMT( head.ZA(), head.AWR() ),
    isotopes( readIsotopes( head, begin, end, lineNumber ) ) {

      readSEND( begin, end, lineNumber, MAT, 2 );
  } catch( std::exception& e ){
    Log::info( "Trouble while reading section 151 of File 2 of Material {}",
               MAT );
    throw e;
  }
