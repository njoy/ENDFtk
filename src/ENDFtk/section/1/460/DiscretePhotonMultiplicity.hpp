/**
 *  @class
 *  @brief Discrete photon multiplicity data
 *
 *  See ENDF102, section 1.6 for more information.
 */
class DiscretePhotonMultiplicity : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/1/460/DiscretePhotonMultiplicity/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the photon energy
   */
  double E() const { return TabulationRecord::C1(); }

  /**
   *  @brief Return the photon energy
   */
  double energy() const { return this->E(); }

  /**
   *  @brief Return the photon index (between 1 and NG)
   */
  int LPH() const { return TabulationRecord::L1(); }

  /**
   *  @brief Return the photon index (between 1 and NG)
   */
  int index() const { return this->LPH(); }

  /**
   *  @brief Return the time values
   */
  auto time() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the time dependent multiplicity values (in units of 1/s)
   */
  auto multiplicities() const { return TabulationRecord::y(); }

  using TabulationRecord::x;
  using TabulationRecord::y;
  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
