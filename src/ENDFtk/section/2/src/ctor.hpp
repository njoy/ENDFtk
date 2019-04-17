/** 
 *  @brief Special case constructor (only scattering radius is given)
 *
 *  @param[in] zaid   the material ZAID value
 *  @param[in] awr    the atomic weight ratio
 *  @param[in] el     the lower limit of the resonance range
 *  @param[in] eh     the upper limit of the resonance range
 *  @param[in] spin   the spin of the target nucleus
 *  @param[in] ap     the scattering radius (inunits of 10^-12 cm)
 */
Type( double zaid, double awr, double el, double eh, double spin, double ap ) :
  Base( zaid, awr, 151 ),
  isotopes( 1,
            { zaid, awr, 0,
              { 1, resonanceParameters::SpecialCase( el, eh, spin, ap ) } } ) {}

template< typename Iterator >
Type ( const HEAD& head, 
       Iterator& begin, 
       const Iterator& end, 
       long& lineNumber, 
       int MAT )
  try: 
    Base( head, MAT, 2 ),
    isotopes( readIsotopes( head, begin, end, lineNumber ) ) {
  } catch( std::exception& e ){
    Log::info( "Trouble while reading section {} of File 2 of Material {}",
               head.MT(), MAT );
    throw e;
  }

