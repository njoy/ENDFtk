/**
 *  @class
 *  @brief Scattering law for the principal scatterer are analytical functions
 *
 *  The AnalyticalFunctions class is used to represent the case in which the
 *  incoherent inelastic thermal scattering law of the principal scatterer in
 *  ENDF section MF4/MT4 is represented entirely by analytical functions.
 *
 *  This class contains no data. The methods defined for this class allow for it
 *  to function in a variant along with other scattering law representation
 *  types.
 *
 *  See ENDF102, section 7.5 for more information.
 */
class AnalyticalFunctions {

public:

  /**
   *  @brief Return the number of lines for this ENDF component
   */
  static constexpr long NC() { return 0; }

  /**
   *  @brief Print this ENDF component
   */
  template< typename OutputIterator >
  void print( OutputIterator&, int, int, int ) const { return; }
};
