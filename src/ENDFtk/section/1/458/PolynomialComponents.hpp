/**
 *  @class
 *  @brief Polynomial evaluation for fission energy release components
 *
 *  The polynomial evaluation for fission energy release components uses
 *  a polynomial expansion to model dependence on incident neutron energy.
 *
 *  See ENDF102, section 1.5 for more information.
 */
class PolynomialComponents : protected ListRecord {

public:

  /* type aliases */
  using Piece = StrideRange< DropRange< ChunkRange< AllRange< double > > > >;

private:

  /* auxiliary functions */
  #include "ENDFtk/section/1/458/PolynomialComponents/src/verify.hpp"
  #include "ENDFtk/section/1/458/PolynomialComponents/src/generateList.hpp"
  #include "ENDFtk/section/1/458/PolynomialComponents/src/createRangeFromIndex.hpp"

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
  int NPLY() const { return ListRecord::L2(); }

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

    return ranges::cpp20::views::iota( 0, 9 )
             | ranges::cpp20::views::transform(
                 [&] ( unsigned int index )
                     { return this->createRangeFromIndex( index ); } );
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
  Piece EFR() const {  return this->createRangeFromIndex( 0 ); }

  /**
   *  @brief Return the kinetic energy of the fission fragments and its
   *         uncertainty
   */
  Piece fissionFragments() const { return this->EFR(); }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons and its
   *         uncertainty
   */
  Piece ENP() const { return this->createRangeFromIndex( 1 ); }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons and its
   *         uncertainty
   */
  Piece promptNeutrons() const { return this->ENP(); }

  /**
   *  @brief Return the kinetic energy of the delayed fission neutrons and its
   *         uncertainty
   */
  Piece END() const { return this->createRangeFromIndex( 2 ); }

  /**
   *  @brief Return the kinetic energy of the delayed fission neutrons and its
   *         uncertainty
   */
  Piece delayedNeutrons() const { return this->END(); }

  /**
   *  @brief Return the energy release by prompt gammas and its uncertainty
   */
  Piece EGP() const { return this->createRangeFromIndex( 3 ); }

  /**
   *  @brief Return the energy release by prompt gammas and its uncertainty
   */
  Piece promptGammas() const { return this->EGP(); }

  /**
   *  @brief Return the energy release by delayed gammas and its uncertainty
   */
  Piece EGD() const { return this->createRangeFromIndex( 4 ); }

  /**
   *  @brief Return the energy release by delayed gammas and its uncertainty
   */
  Piece delayedGammas() const { return this->EGD(); }

  /**
   *  @brief Return the energy release by delayed betas and its uncertainty
   */
  Piece EB() const { return this->createRangeFromIndex( 5 ); }

  /**
   *  @brief Return the energy release by delayed betas and its uncertainty
   */
  Piece delayedBetas() const  { return this->EB(); }

  /**
   *  @brief Return the energy release by neutrinos and its uncertainty
   */
  Piece ENU() const { return this->createRangeFromIndex( 6 ); }

  /**
   *  @brief Return the energy release by neutrinos and its uncertainty
   */
  Piece neutrinos() const { return this->ENU(); }

  /**
   *  @brief Return the total energy release minus the neutrino energy and its
   *         uncertainty
   */
  Piece ER() const { return this->createRangeFromIndex( 7 ); }

  /**
   *  @brief Return the total energy release minus the neutrino energy and its
   *         uncertainty
   */
  Piece totalMinusNeutrinos() const  { return this->ER(); }

  /**
   *  @brief Return the total energy release and its uncertainty
   */
  Piece ET() const  { return this->createRangeFromIndex( 8 ); }

  /**
   *  @brief Return the total energy release and its uncertainty
   */
  Piece total() const  { return this->ET(); }

  using ListRecord::NC;
  using ListRecord::print;
};
