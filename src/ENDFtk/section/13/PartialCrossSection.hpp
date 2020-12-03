/**
 *  @class
 *  @brief A partial photon production cross section (either for the continuum
 *         or a discrete photon).
 *
 *  See ENDF102, section 13.2 for more information.
 */
class PartialCrossSection : protected TabulationRecord {

  /* auxiliary functions */

public:
  /* constructor */
  #include "ENDFtk/section/13/PartialCrossSection/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double ES() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double levelEnergy() const { return this->ES(); }

  /**
   *  @brief Return the photon energy or the binding energy
   */
  double EG() const { return TabulationRecord::C1(); }

  /**
  *  @brief Return the photon energy or the binding energy
   */
  double photonOrBindingEnergy() const { return this->EG(); }

  /**
   *  @brief Return the primary photon flag value
   */
  int LP() const { return TabulationRecord::L1(); }

  /**
   *  @brief Return the primary photon flag value
   */
  int primaryPhotonFlag() const { return this->LP(); }

  /**
   *  @brief Return the photon energy distribution law number
   */
  int LF() const { return TabulationRecord::L2(); }

  /**
   *  @brief Return the photon energy distribution law number
   */
  int LAW() const { return this->LF(); }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the incident energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the cross section values
   */
  auto XS() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const { return this->XS(); }

  using TabulationRecord::NR;
  using TabulationRecord::NP;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::x;
  using TabulationRecord::y;
  using TabulationRecord::regions;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
