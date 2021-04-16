/**
 *  @class
 *  @brief Tabulated evaluation for fission energy release components
 *
 *  The tabulated evaluation for fission energy release components uses
 *  a thermal point evaluation for the energy release components, with in
 *  addition some tabulated components.
 *
 *  See ENDF102, section 1.5 for more information.
 */
class TabulatedComponents {

public:

  /* type aliases */
  using OptionalEnergyReleaseComponent = std::optional< EnergyReleaseComponent >;

private:

  /* fields */
  int nfc_;
  ThermalPointComponents values_;
  std::array< OptionalEnergyReleaseComponent, 9 > components_;

  /* auxiliary functions */
  #include "ENDFtk/section/1/458/TabulatedComponents/src/generateTables.hpp"
  #include "ENDFtk/section/1/458/TabulatedComponents/src/readTables.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/1/458/TabulatedComponents/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the tabulated energy release flag
   */
  static constexpr int LFC() { return 1; }

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
  int NFC() const { return this->nfc_; }

  /**
   *  @brief Return the number of tabulated energy release components
   */
  int numberTabulatedComponents() const { return this->NFC(); }

  /**
   *  @brief Return the thermal point values
   */
  const ThermalPointComponents& thermalPointValues() const {

    return this->values_;
  }

  /**
   *  @brief Return the tabulated kinetic energy of the fission fragments
   */
  const std::array< OptionalEnergyReleaseComponent, 9 >& tabulated() const {

    return this->components_;
  }

  /**
   *  @brief Return the tabulated kinetic energy of the fission fragments
   */
  const OptionalEnergyReleaseComponent& tabulatedEFR() const {

    return std::get< 0 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated kinetic energy of the fission fragments
   */
  const OptionalEnergyReleaseComponent& tabulatedFissionFragments() const {

    return this->tabulatedEFR();
  }

  /**
   *  @brief Return the tabulated kinetic energy of the prompt fission neutrons
   */
  const OptionalEnergyReleaseComponent& tabulatedENP() const {

    return std::get< 1 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated kinetic energy of the prompt fission neutrons
   */
  const OptionalEnergyReleaseComponent& tabulatedPromptNeutrons() const {

    return this->tabulatedENP();
  }

  /**
   *  @brief Return the tabulated kinetic energy of the delayed fission neutrons
   */
  const OptionalEnergyReleaseComponent& tabulatedEND() const {

    return std::get< 2 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated kinetic energy of the delayed fission neutrons
   */
  const OptionalEnergyReleaseComponent& tabulatedDelayedNeutrons() const {

    return this->tabulatedEND();
  }

  /**
   *  @brief Return the tabulated energy release by prompt gammas
   */
  const OptionalEnergyReleaseComponent& tabulatedEGP() const {

    return std::get< 3 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated energy release by prompt gammas
   */
  const OptionalEnergyReleaseComponent& tabulatedPromptGammas() const {

    return this->tabulatedEGP();
  }

  /**
   *  @brief Return the tabulated energy release by delayed gammas
   */
  const OptionalEnergyReleaseComponent& tabulatedEGD() const {

    return std::get< 4 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated energy release by delayed gammas
   */
  const OptionalEnergyReleaseComponent& tabulatedDelayedGammas() const {

    return this->tabulatedEGD();
  }

  /**
   *  @brief Return the tabulated energy release by delayed betas
   */
  const OptionalEnergyReleaseComponent& tabulatedEB() const {

    return std::get< 5 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated energy release by delayed betas
   */
  const OptionalEnergyReleaseComponent& tabulatedDelayedBetas() const {

    return this->tabulatedEB();
  }

  /**
   *  @brief Return the tabulated energy release by neutrinos
   */
  const OptionalEnergyReleaseComponent& tabulatedENU() const {

    return std::get< 6 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated energy release by neutrinos
   */
  const OptionalEnergyReleaseComponent& tabulatedNeutrinos() const {

    return this->tabulatedENU();
  }

  /**
   *  @brief Return the tabulated total energy release minus the neutrino energy
   */
  const OptionalEnergyReleaseComponent& tabulatedER() const {

    return std::get< 7 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated total energy release minus the neutrino energy
   */
  const OptionalEnergyReleaseComponent& tabulatedTotalMinusNeutrinos() const {

    return this->tabulatedER();
  }

  /**
   *  @brief Return the tabulated total energy release
   */
  const OptionalEnergyReleaseComponent& tabulatedET() const {

    return std::get< 8 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated total energy release
   */
  const OptionalEnergyReleaseComponent& tabulatedTotal() const {

    return this->tabulatedET();
  }

  #include "ENDFtk/section/1/458/TabulatedComponents/src/NC.hpp"
  #include "ENDFtk/section/1/458/TabulatedComponents/src/print.hpp"
};
