/**
 *  @class
 *  @brief Outgoing energy distribution for a fixed value of E
 *
 *  The OutgoingDistribution class is used to represent the outgoing energy
 *  distribution for a fixed value of E from an ENDF MF5 section.
 *
 *  See ENDF102, section 5.2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT OutgoingEnergyDistribution : 
    protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/5/TabulatedSpectrum/OutgoingEnergyDistribution/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the incident energy value
   */
  auto E() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the incident energy value
   */
  auto incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the outgoing energy values
   */
  auto EP() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the outgoing energy values
   */
  auto outgoingEnergies() const { return this->EP(); }

  /**
   *  @brief Return the distribution values
   */
  auto G() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the distribution values
   */
  auto probabilities() const { return this->G(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
