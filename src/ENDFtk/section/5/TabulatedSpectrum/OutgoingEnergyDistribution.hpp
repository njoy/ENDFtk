/**
 *  @class
 *  @brief g(E->E') data for a fixed value of E
 *
 *  The OutgoingDistribution class is used to represent the outgoing energy 
 *  distribution for a fixed value of E from an ENDF MF5 section.
 *
 *  See ENDF102, section 5.2.1 for more information.
 */
class OutgoingEnergyDistribution : protected TabulationRecord {

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
  auto incomingEnergy() const { return this->E(); }

  /**
   *  @brief Return the energy values
   */
  auto EPRIME() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energy values
   */
  auto outgoingEnergies() const { return this->EPRIME(); }

  /**
   *  @brief Return the probability values
   */
  auto g() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the probability values
   */
  auto probabilities() const { return this->g(); }

  /**
   *  @brief Return the number of outgoing energy values
   */
  auto NF() const { return TabulationRecord::NP(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
