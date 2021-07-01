/**
 *  @class
 *  @brief The secondary energy distribution associated to a given cosine
 *         value
 *
 *  See ENDF102, section 12.2.8 for more information.
 */
class EnergyDistribution : protected TabulationRecord {

public:
  /* constructor */
  #include "ENDFtk/section/6/LaboratoryAngleEnergy/EnergyDistribution/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of interpolation regions for the secondary energy
   */
  long NRP() const { return TabulationRecord::NR(); }

  /**
   *  @brief Return the number of secondary energy values
   */
  long NEP() const { return TabulationRecord::NP(); }

  /**
   *  @brief Return the cosine value for this secondary energy distribition
   */
  double MU() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the cosine value for this secondary energy distribition
   */
  double cosine() const { return this->MU(); }

  /**
   *  @brief Return the outgoing energy values
   */
  AllRange< double > EP() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the outgoing energy values
   */
  AllRange< double > energies() const { return this->EP(); }

  /**
   *  @brief Return the probabilities
   */
  AllRange< double > F() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the probabilities
   */
  AllRange< double > probabilities() const { return  this->F(); }

  using TabulationRecord::NR;
  using TabulationRecord::NP;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
