/**
 *  @class
 *  @brief The Madland Nix fission neutron spectrum (LF=12)
 *
 *  See ENDF102, section 5.1.1.6 and 5.2.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT MadlandNixSpectrum : protected TabulationRecord {

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
  int LAW() const { return this->LF(); }

  /**
   *  @brief Return the average kinetic energy of the average light
   *         fission fragment (the EFL value)
   */
  double EFL() const { return TabulationRecord::C1(); }

  /**
   *  @brief Return the average kinetic energy of the average light
   *         fission fragment (the EFL value)
   */
  double lightFragmentEnergy() const { return this->EFL(); }

  /**
   *  @brief Return the average kinetic energy of the average heavy
   *         fission fragment (the EFL value)
   */
  double EFH() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the average kinetic energy of the average heavy
   *         fission fragment (the EFL value)
   */
  double heavyFragmentEnergy() const { return this->EFH(); }

  /**
   *  @brief Return the energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the maximum temperature parameter values
   */
  auto TM() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the maximum temperature parameter values
   */
  auto maximumTemperatureValues() const { return this->TM(); }

  using TabulationRecord::NP;
  using TabulationRecord::numberPoints;
  using TabulationRecord::NR;
  using TabulationRecord::numberInterpolationRegions;
  using TabulationRecord::INT;
  using TabulationRecord::interpolants;
  using TabulationRecord::NBT;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
