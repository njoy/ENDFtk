/** 
 *  @brief Constructor (components)
 *
 *  The number of entries in the temperatures array is checked against the
 *  temperature dependence flag LT (the L1 value on the TabulationRecord).
 *
 *  @param[in] principal      the TabulationRecord to be moved into the object
 *  @param[in] temperatures   an array of ListRecord, one for each additional
 *                            temperature to be moved into the object
 */
CoherentElastic( TabulationRecord&& principal,
                 std::vector< ListRecord >&& temperatures ) :
  principal_( std::move( principal ) ),
  temperatures_( std::move( temperatures ) ) {

  verifyLT( this->LT(), this->NT() );
}

/** 
 *  @brief Constructor (multiple temperatures)
 *
 *  The size of the various arrays is checked for consistency where appropriate.
 *
 *  @param[in] boundaries     the interpolation range boundaries for S(E)
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] temperatures   the temperatures (NT values)
 *  @param[in] li             the temperature interpolation flags (NT-1 values)
 *  @param[in] energies       the energy values (NP values)
 *  @param[in] s              the thermal scattering values (NT arrays of NP
 *                            values)
 */
CoherentElastic( std::vector< long >&& boundaries,
                 std::vector< long >&& interpolants,
                 std::vector< double >&& temperatures,
                 std::vector< long >&& li,
                 std::vector< double >&& energies,
                 std::vector< std::vector< double > >&& s ) :
  CoherentElastic( TabulationRecord( temperatures[0], 0,
                                     temperatures.size() - 1, 0,
                                     std::move( boundaries ),
                                     std::move( interpolants ),
                                     std::move( energies ),
                                     std::move( s[0] ) ),
                   generateTemperatures( std::move( temperatures ),
                                         std::move( li ),
                                         std::move( s ) ) ) {}

/** 
 *  @brief Constructor (single temperature)
 *
 *  The size of the various arrays is checked for consistency where appropriate.
 *
 *  @param[in] temperature    the temperature
 *  @param[in] boundaries     the interpolation range boundaries for S(E)
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] energies       the energy values (NP values)
 *  @param[in] s              the thermal scattering values (NP values)
 */
CoherentElastic( double temperature,
                 std::vector< long >&& boundaries,
                 std::vector< long >&& interpolants,
                 std::vector< double >&& energies,
                 std::vector< double >&& s ) :
  CoherentElastic( TabulationRecord( temperature, 0, 0, 0,
                                     std::move( boundaries ),
                                     std::move( interpolants ),
                                     std::move( energies ),
                                     std::move( s ) ), {} ) {}

private:
/** 
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
CoherentElastic( TabulationRecord&& principal,
                 Iterator& begin,
                 const Iterator& end,
                 long& lineNumber,
                 int MAT,
                 int MF,
                 int MT ) :
  CoherentElastic( std::move( principal ),
                   readTemperatures( begin, end, lineNumber,
                                     MAT, MF, MT, principal.L1() ) ) {}

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
CoherentElastic( Iterator& begin,
                 const Iterator& end,
                 long& lineNumber,
                 int MAT,
                 int MF,
                 int MT ) :
  CoherentElastic( TabulationRecord( begin, end, lineNumber, MAT, MF, MT ),
                   begin, end, lineNumber, MAT, MF, MT ) {}

