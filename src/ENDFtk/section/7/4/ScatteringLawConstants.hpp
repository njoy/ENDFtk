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

    auto indices = [] (auto NS) {
      switch(1 + NS) {
        case 1: {
          static constexpr std::array< std::ptrdiff_t, 1 > indices = {{0}};
          return ranges::make_subrange(indices.begin(), indices.end());
        } case 2: {
          static constexpr std::array< std::ptrdiff_t, 2 > indices = {{0, 7}};
          return ranges::make_subrange(indices.begin(), indices.end());
        } case 3: {
          static constexpr std::array< std::ptrdiff_t, 3 > indices = {{0, 7, 13}};
          return ranges::make_subrange(indices.begin(), indices.end());
        } case 4: {
          static constexpr std::array< std::ptrdiff_t, 4 > indices = {{0, 7, 13, 19}};
          return ranges::make_subrange(indices.begin(), indices.end());
        } default: {
         #ifdef __GNUC__
          __builtin_unreachable();
         #endif
         throw std::logic_error("Illegal NS");
        }
      }
    };

    auto element = [l = ListRecord::list()](auto index){ return l[index]; };

    return indices( this->NS() ) | ranges::cpp20::views::transform( element );
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
  StrideRange< DropRange< AllRange< double > > > AWR() const {

    return ListRecord::list()
             | ranges::views::drop_exactly( 2 )
             | ranges::views::stride( 6 ); }

  /**
   *  @brief Return the ratio of the atomic weight to the neutron mass for each
   *         scattering atom type, stored in B(3), B(9) and B(15)
   */
  StrideRange< DropRange< AllRange< double > > > atomicWeightRatios() const {

    return this->AWR();
  }

  /**
   *  @brief Return the number of atoms for each scattering atom type present in
   *         the molecule or unit cell, stored in B(6), B(12) and B(18)
   */
  StrideRange< DropRange< AllRange< double > > > M() const {

    return ListRecord::list()
             | ranges::views::drop_exactly( 5 )
             | ranges::views::stride( 6 ); }

  /**
   *  @brief Return the number of atoms for each scattering atom type present in
   *         the molecule or unit cell, stored in B(6), B(12) and B(18)
   */
  StrideRange< DropRange< AllRange< double > > > numberAtoms() const {

    return this->M();
  }

  /**
   *  @brief Return the analytical function type for each non-principal
   *         scattering atom type, stored in B(7), B(13) and B(19)
   */
  StrideRange< DropRange< AllRange< double > > >
  analyticalFunctionTypes() const {

    return ListRecord::list()
             | ranges::views::drop_exactly( 6 )
             | ranges::views::stride( 6 );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
