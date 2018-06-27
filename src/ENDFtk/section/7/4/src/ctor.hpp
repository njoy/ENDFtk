/** 
 *  @brief Constructor
 *
 *  @param[in] constants               the thermal scattering law constants
 *  @param[in] law                     the thermal scattering law
 *  @param[in] principalTemperature    the effective temperature of the
 *                                     principal scatterer
 *  @param[in] secondaryTemperatures   the effective temperature of the
 *                                     secondary scatterers (if required)
 */
Type( double zaid, double awr, int lat, int lasym,
      ScatteringLawConstants&& constants,
      ScatteringLaw&& law,
      EffectiveTemperature&& principalTemperature,
      std::vector< std::optional< EffectiveTemperature > >
          secondaryTemperatures ) :
  Base( 4, zaid, awr ), lat_( lat ), lasym_( lasym ),
  b_( std::move( constants ) ), law_( std::move( law ) ),
  principal_( std::move( principalTemperature ) ),
  secondary_( std::move( secondaryTemperatures ) ) {}

private:
/** 
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
Type( double zaid, double awr, int lat, int lasym,
      ScatteringLawConstants&& constants,
      ScatteringLaw&& law,
      EffectiveTemperature&& principalTemperature,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT,
      int MF,
      int MT ) :
  Type( zaid, awr, lat, lasym,
        std::move( constants ),
        std::move( law ),
        std::move( principalTemperature ),
        readSecondaryTemperatures( begin, end, lineNumber,MAT, MF, MT,
                                   constants.analyticalFunctionTypes() ) ) {}

/** 
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
Type( double zaid, double awr, int lat, int lasym,
      ScatteringLawConstants&& constants,
      ScatteringLaw&& law,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT,
      int MF,
      int MT ) :
  Type( zaid, awr, lat, lasym,
        std::move( constants ),
        std::move( law ),
        EffectiveTemperature( begin, end, lineNumber, MAT, MF, MT ),
        begin, end, lineNumber, MAT, MF, MT ) {}

/** 
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
Type( double zaid, double awr, int lat, int lasym,
      ScatteringLawConstants&& constants,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT,
      int MF,
      int MT ) :
  Type( zaid, awr, lat, lasym,
        std::move( constants ),
        readScatteringLaw( begin, end, lineNumber, MAT, MF, MT,
                           constants.totalFreeCrossSections()[0] ),
        begin, end, lineNumber, MAT, MF, MT ) {}

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
  try : Type( head.ZA(), head.AWR(), head.L2(), head.N1(),
              ScatteringLawConstants( begin, end, lineNumber, MAT, 7, 4 ),
              begin, end, lineNumber, MAT, 7, 4 ) {
    readSEND(begin, end, lineNumber, MAT, 7 );
  } catch ( std::exception& e ) {
    Log::info( "Trouble while reading section 4 of File 7 of Material {}",
               MAT );
    throw e;
  }


