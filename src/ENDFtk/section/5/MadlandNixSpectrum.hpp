/**
 *  @class
 *  @brief The Madland Nix fission neutron spectrum (LF=12)
 *
 *  See ENDF102, section 5.1.1.6 for more information.
 */
class MadlandNixSpectrum : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/5/MadlandNixSpectrum/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int LF() { return 12; }

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int distributionType() { return MadlandNixSpectrum::LF(); }

  /**
   *  @brief Return the average kinetic energy of the average light
   *         fission fragment (the EFL value)
   */
  double EFL() const { return TabulationRecord::C1(); }

  /**
   *  @brief Return the average kinetic energy of the average light
   *         fission fragment (the EFL value)
   */
  double lightKineticEnergy() const { return this->EFL(); }

  /**
   *  @brief Return the average kinetic energy of the average heavy
   *         fission fragment (the EFL value)
   */
  double EFH() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the average kinetic energy of the average heavy
   *         fission fragment (the EFL value)
   */
  double heavyKineticEnergy() const { return this->EFH(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the probability values
   */
  auto maximumTemperatureValues() const { return TabulationRecord::y(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
