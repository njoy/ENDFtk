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
 *  See ENDF102, section 7.5 for more information.
 */
class ENDFTK_PYTHON_EXPORT ScatteringLawConstants : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/7/4/ScatteringLawConstants/src/generateList.hpp"
  #include "ENDFtk/section/7/4/ScatteringLawConstants/src/verifySize.hpp"
  #include "ENDFtk/section/7/4/ScatteringLawConstants/src/checkLLN.hpp"

  /* workaround for the removal of range-v3 */

  std::vector< double > sigma_;
  #include "ENDFtk/section/7/4/ScatteringLawConstants/src/generateSigma.hpp"

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
  double EMAX() const { return ListRecord::list()[3]; }

  /**
   *  @brief Return the upper energy limit of the thermal scattering law,
             stored in B(4)
   */
  double upperEnergyLimit() const { return this->EMAX(); }

  /**
   *  @brief Return the total free atom cross section for each scattering atom
   *         type, stored in B(1), B(8) and B(14)
   */
  auto MSIGMA() const {

    using namespace njoy::tools;
    return std20::views::all( this->sigma_ );
  }

  /**
   *  @brief Return the total free atom cross section for each scattering atom
   *         type, stored in B(1), B(8) and B(14)
   */
  auto totalFreeCrossSections() const { return this->MSIGMA(); }

  /**
   *  @brief Return the ratio of the atomic weight to the neutron mass for each
   *         scattering atom type, stored in B(3), B(9) and B(15)
   */
  auto AWR() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( 2 )
             | std23::views::stride( 6 ); }

  /**
   *  @brief Return the ratio of the atomic weight to the neutron mass for each
   *         scattering atom type, stored in B(3), B(9) and B(15)
   */
  auto atomicWeightRatios() const {

    return this->AWR();
  }

  /**
   *  @brief Return the number of atoms for each scattering atom type present in
   *         the molecule or unit cell, stored in B(6), B(12) and B(18)
   */
  auto M() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( 5 )
             | std23::views::stride( 6 ); }

  /**
   *  @brief Return the number of atoms for each scattering atom type present in
   *         the molecule or unit cell, stored in B(6), B(12) and B(18)
   */
  auto numberAtoms() const {

    return this->M();
  }

  /**
   *  @brief Return the analytical function type for each non-principal
   *         scattering atom type, stored in B(7), B(13) and B(19)
   */
  auto analyticalFunctionTypes() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( 6 )
             | std23::views::stride( 6 );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
