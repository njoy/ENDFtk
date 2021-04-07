/**
 *  @class
 *  @brief Thermal point evaluation for fission energy release components
 *
 *  The thermal point evaluation for fission energy release components uses
 *  analytical functions to model dependence on incident neutron energy.
 *
 *  See ENDF102, section 1.5 for more information.
 */
class ThermalPointComponents : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/1/458/ThermalPointComponents/src/verify.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/1/458/ThermalPointComponents/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the tabulated energy release flag
   */
  static constexpr bool LFC() { return false; }

  /**
   *  @brief Return the tabulated energy release flag
   */
  bool tabulatedEnergyRelease() const { return this->LFC(); }

  /**
   *  @brief Return the polynomial expansion order
   */
  static constexpr int NPLY() { return 0; }

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
  ChunkRange< AllRange< double > > E() const {

    return ListRecord::list() | ranges::views::chunk( 2 );
  }

  /**
   *  @brief Return the energy release values and their uncertainties
   *
   *  This returns a range of pairs (the energy release value and its
   *  uncertainty)
   */
  ChunkRange< AllRange< double > > energyRelease() const { return this->E(); }

  /**
   *  @brief Return the kinetic energy of the fission fragments and its
   *         uncertainty
   */
  Chunk< AllRange< double > > EFR() const { return this->E()[0]; }

  /**
   *  @brief Return the kinetic energy of the fission fragments and its
   *         uncertainty
   */
  Chunk< AllRange< double > > fissionFragments() const { return this->EFR(); }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons and its
   *         uncertainty
   */
  Chunk< AllRange< double > > ENP() const { return this->E()[1]; }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons and its
   *         uncertainty
   */
  Chunk< AllRange< double > > promptNeutrons() const { return this->ENP(); }

  /**
   *  @brief Return the kinetic energy of the delayed fission neutrons and its
   *         uncertainty
   */
  Chunk< AllRange< double > > END() const { return this->E()[2]; }

  /**
   *  @brief Return the kinetic energy of the delayed fission neutrons and its
   *         uncertainty
   */
  Chunk< AllRange< double > > delayedNeutrons() const { return this->END(); }

  /**
   *  @brief Return the energy release by prompt gammas and its uncertainty
   */
  Chunk< AllRange< double > > EGP() const { return this->E()[3]; }

  /**
   *  @brief Return the energy release by prompt gammas and its uncertainty
   */
  Chunk< AllRange< double > > promptGammas() const { return this->EGP(); }

  /**
   *  @brief Return the energy release by delayed gammas and its uncertainty
   */
  Chunk< AllRange< double > > EGD() const { return this->E()[4]; }

  /**
   *  @brief Return the energy release by delayed gammas and its uncertainty
   */
  Chunk< AllRange< double > > delayedGammas() const { return this->EGD(); }

  /**
   *  @brief Return the energy release by delayed betas and its uncertainty
   */
  Chunk< AllRange< double > > EB() const  { return this->E()[5]; }

  /**
   *  @brief Return the energy release by delayed betas and its uncertainty
   */
  Chunk< AllRange< double > > delayedBetas() const  { return this->EB(); }

  /**
   *  @brief Return the energy release by neutrinos and its uncertainty
   */
  Chunk< AllRange< double > > ENU() const { return this->E()[6]; }

  /**
   *  @brief Return the energy release by neutrinos and its uncertainty
   */
  Chunk< AllRange< double > > neutrinos() const { return this->ENU(); }

  /**
   *  @brief Return the total energy release minus the neutrino energy and its
   *         uncertainty
   */
  Chunk< AllRange< double > > ER() const  { return this->E()[7]; }

  /**
   *  @brief Return the total energy release minus the neutrino energy and its
   *         uncertainty
   */
  Chunk< AllRange< double > > totalMinusNeutrinos() const  { return this->ER(); }

  /**
   *  @brief Return the total energy release and its uncertainty
   */
  Chunk< AllRange< double > > ET() const  { return this->E()[8]; }

  /**
   *  @brief Return the total energy release and its uncertainty
   */
  Chunk< AllRange< double > > total() const  { return this->ET(); }

  using ListRecord::NC;
  using ListRecord::print;
};
