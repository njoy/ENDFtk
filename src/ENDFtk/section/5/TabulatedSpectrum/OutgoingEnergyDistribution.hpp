/**
 *  @class
 *  @brief g(E') data for a fixed value of E
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
  auto incidentEnergy() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the probability values
   */
  auto probabilities() const { return TabulationRecord::y(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};