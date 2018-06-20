class ScatteringLawConstants : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/7/4/ScatteringLawConstants/src/generateList.hpp"
  #include "ENDFtk/section/7/4/ScatteringLawConstants/src/verifySize.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/7/4/ScatteringLawConstants/src/ctor.hpp"

  /* get methods */

  /**
   * @brief Return the LLN flag (either S or ln(S) is stored)
   */
  int LLN() const { return ListRecord::L1(); }

  /**
   * @brief Return the size of the B array, equal to 6*(NS+1)
   */
  long NI() const { return ListRecord::NPL(); }

  /**
   * @brief Return the number of non-principal scattering atom types
   */
  long NS() const { return ListRecord::N2(); }

  /**
   * @brief Return the value of epsilon = E/kT, stored in B(2)
   */
  double epsilon() const { return ListRecord::list()[1]; }

  /**
   * @brief Return the upper energy limit of the thermal scattering law,
            stored in B(4)
   */
  double upperEnergyLimit() const { return ListRecord::list()[3]; }

  /**
   * @brief Return the total free atom cross section for each scattering atom
   *        type, stored in B(1), B(8) and B(14)
   */
//  auto totalFreeCrossSections() const {
//    return ListRecord::list()[0]; }
// TEMPORARY - REALLY BAD
  std::vector< double > totalFreeCrossSections() const {
    if ( this->NI() == 6 ) return { ListRecord::list()[0] };
    if ( this->NI() == 12 ) return { ListRecord::list()[0],
                                     ListRecord::list()[7] };
    if ( this->NI() == 18 ) return { ListRecord::list()[0],
                                     ListRecord::list()[7],
                                     ListRecord::list()[13] };
    return {};
  }
// TEMPORARY - REALLY BAD

  /**
   * @brief Return the ratio of the atomic weight to the neutron mass for each
   *        scattering atom type, stored in B(3), B(9) and B(15)
   */
  auto atomicWeightRatios() const {
    return ranges::view::drop_exactly( ListRecord::list(), 2 )
             | ranges::view::stride( 6 ); }

  /**
   * @brief Return the number of atoms for each scattering atom type present in
   *        the molecule or unit cell, stored in B(6), B(12) and B(18)
   */
  auto numberAtoms() const {
    return ranges::view::drop_exactly( ListRecord::list(), 5 )
             | ranges::view::stride( 6 ); }

  /**
   * @brief Return the analytical function type for each non-principal
   *        scattering atom type, stored in B(7) and B(13)
   */
  auto analyticalFunctionTypes() const {
    return ranges::view::drop_exactly( ListRecord::list(), 6 )
             | ranges::view::stride( 6 ); }

  using ListRecord::NC;
  using ListRecord::print;
};
