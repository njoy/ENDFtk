/**
 *  @class
 *  @brief Polynomial evaluation for fission energy release components
 *
 *  The polynomial evaluation for fission energy release components uses
 *  a polynomial expansion to model dependence on incident neutron energy.
 *
 *  See ENDF102, section 1.5 for more information.
 */
class ENDFTK_PYTHON_EXPORT PolynomialComponents {

  /* workaround for the removal of range-v3 */

  // using transform with more ranges operations in the transform causes issues
  // on the Python side. we just rearrange the underlying array at construction
  // time to solve it. As a result, this no longer inherits from ListRecord.
  int nply_;
  std::vector< double > values_;

  /* auxiliary functions */
  #include "ENDFtk/section/1/458/PolynomialComponents/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/1/458/PolynomialComponents/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the tabulated energy release flag
   */
  static constexpr int LFC() { return 0; }

  /**
   *  @brief Return the tabulated energy release flag
   */
  bool tabulatedEnergyRelease() const { return this->LFC(); }

  /**
   *  @brief Return the polynomial expansion order
   */
  int NPLY() const { return this->nply_; }

  /**
   *  @brief Return the polynomial expansion order
   */
  int order() const { return this->NPLY(); }

  /**
   *  @brief Return the number of tabulated energy release components
   */
  static constexpr int NFC() { return 0; }

  /**
   *  @brief Return the number of tabulated energy release components
   */
  int numberTabulatedComponents() const { return this->NFC(); }

  /**
   *  @brief Return the energy release values and their uncertainties
   *
   *  This returns a range of pairs (the energy release value and its
   *  uncertainty)
   */
  auto E() const {

    using namespace njoy::tools;
    return this->values_ | std23::views::chunk( 2 )
                         | std23::views::chunk( this->order() + 1 );
  }

  /**
   *  @brief Return the energy release values and their uncertainties
   *
   *  This returns a range of pairs (the energy release value and its
   *  uncertainty)
   */
  auto energyRelease() const { return this->E(); }

  /**
   *  @brief Return the kinetic energy of the fission fragments and its
   *         uncertainty
   */
  auto EFR() const { return this->E()[0]; }

  /**
   *  @brief Return the kinetic energy of the fission fragments and its
   *         uncertainty
   */
  auto fissionFragments() const { return this->EFR(); }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons and its
   *         uncertainty
   */
  auto ENP() const { return this->E()[1]; }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons and its
   *         uncertainty
   */
  auto promptNeutrons() const { return this->ENP(); }

  /**
   *  @brief Return the kinetic energy of the delayed fission neutrons and its
   *         uncertainty
   */
  auto END() const { return this->E()[2]; }

  /**
   *  @brief Return the kinetic energy of the delayed fission neutrons and its
   *         uncertainty
   */
  auto delayedNeutrons() const { return this->END(); }

  /**
   *  @brief Return the energy release by prompt gammas and its uncertainty
   */
  auto EGP() const { return this->E()[3]; }

  /**
   *  @brief Return the energy release by prompt gammas and its uncertainty
   */
  auto promptGammas() const { return this->EGP(); }

  /**
   *  @brief Return the energy release by delayed gammas and its uncertainty
   */
  auto EGD() const { return this->E()[4]; }

  /**
   *  @brief Return the energy release by delayed gammas and its uncertainty
   */
  auto delayedGammas() const { return this->EGD(); }

  /**
   *  @brief Return the energy release by delayed betas and its uncertainty
   */
  auto EB() const { return this->E()[5]; }

  /**
   *  @brief Return the energy release by delayed betas and its uncertainty
   */
  auto delayedBetas() const  { return this->EB(); }

  /**
   *  @brief Return the energy release by neutrinos and its uncertainty
   */
  auto ENU() const { return this->E()[6]; }

  /**
   *  @brief Return the energy release by neutrinos and its uncertainty
   */
  auto neutrinos() const { return this->ENU(); }

  /**
   *  @brief Return the total energy release minus the neutrino energy and its
   *         uncertainty
   */
  auto ER() const { return this->E()[7]; }

  /**
   *  @brief Return the total energy release minus the neutrino energy and its
   *         uncertainty
   */
  auto totalMinusNeutrinos() const  { return this->ER(); }

  /**
   *  @brief Return the total energy release and its uncertainty
   */
  auto ET() const  { return this->E()[8]; }

  /**
   *  @brief Return the total energy release and its uncertainty
   */
  auto total() const  { return this->ET(); }

  /**
   *  @brief Return the number of lines in this MF1/MT458 component
   */
  long NC() const {

    return 1 + ( this->order() + 1 ) * 3;
  }

  #include "ENDFtk/section/1/458/PolynomialComponents/src/print.hpp"
};
