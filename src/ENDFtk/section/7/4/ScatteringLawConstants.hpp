/**
 *  @class
 *  @brief Scattering law constants
 *
 *  The ScatteringLawConstants class stores the data from the first ListRecord
 *  of an MF7/MT4 section of the ENDF file. It stores a single flag to indicate
 *  the representation type of the S(a,b) (either as S or ln(S) values) and the
 *  B array containing the  constants required for the scattering law data of
 *  the principal scatterer and the analytic representations for the
 *  non-principal scattering atoms (if any).
 *
 *  See ENDF102, section 7.4 for more information.
 */
class ScatteringLawConstants : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/7/4/ScatteringLawConstants/src/generateList.hpp"
  #include "ENDFtk/section/7/4/ScatteringLawConstants/src/verifySize.hpp"
  #include "ENDFtk/section/7/4/ScatteringLawConstants/src/checkLLN.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/7/4/ScatteringLawConstants/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the LLN flag (either S or ln(S) is stored)
   */
  int LLN() const { return ListRecord::L1(); }

  /**
   *  @brief Return the LLN flag (either S or ln(S) is stored)
   */
  int sabStorageType() const { return this->LLN(); }

  /**
   *  @brief Return the size of the B array, equal to 6*(NS+1)
   */
  long NI() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the size of the B array, equal to 6*(NS+1)
   */
  long numberConstants() const { return this->NI(); }

  /**
   *  @brief Return the number of non-principal scattering atom types
   */
  long NS() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of non-principal scattering atom types
   */
  long numberNonPrincipalScatterers() const { return this->NS(); }

  /**
   *  @brief Return the value of epsilon = E/kT, stored in B(2)
   */
  double epsilon() const { return ListRecord::list()[1]; }

  /**
   *  @brief Return the upper energy limit of the thermal scattering law,
             stored in B(4)
   */
  double upperEnergyLimit() const { return ListRecord::list()[3]; }

  /**
   *  @brief Return the total free atom cross section for each scattering atom
   *         type, stored in B(1), B(8) and B(14)
   */
  auto totalFreeCrossSections() const {

    //! @todo this code no longer works since the ranges update, is there an
    //!       alternative as the current operational code is more of a hack?
    // return ranges::view::concat(
    //          ranges::view::single( ListRecord::list()[0] ), 
    //          ranges::view::drop_exactly( ListRecord::list(), 7 )
    //                | ranges::view::stride( 6 )  );
 
    std::vector< double > result = { ListRecord::list()[0] };
    if ( ListRecord::NPL() > 6 ) { result.push_back( ListRecord::list()[7] ); }
    if ( ListRecord::NPL() > 13 ) { result.push_back( ListRecord::list()[13] ); }
    return result;
  }

  /**
   *  @brief Return the ratio of the atomic weight to the neutron mass for each
   *         scattering atom type, stored in B(3), B(9) and B(15)
   */
  auto atomicWeightRatios() const {
    return ranges::view::drop_exactly( ListRecord::list(), 2 )
             | ranges::view::stride( 6 ); }

  /**
   *  @brief Return the number of atoms for each scattering atom type present in
   *         the molecule or unit cell, stored in B(6), B(12) and B(18)
   */
  auto numberAtoms() const {
    return ranges::view::drop_exactly( ListRecord::list(), 5 )
             | ranges::view::stride( 6 ); }

  /**
   *  @brief Return the analytical function type for each non-principal
   *         scattering atom type, stored in B(7), B(13) and B(19)
   */
  auto analyticalFunctionTypes() const {
    return ranges::view::drop_exactly( ListRecord::list(), 6 )
             | ranges::view::stride( 6 ); }

  using ListRecord::NC;
  using ListRecord::print;
};
