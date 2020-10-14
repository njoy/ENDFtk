/**
 *  @class
 *  @brief A simplified distribution for neutron and charged particles
 *
 *  See ENDF102, section 6.2.5 for more information.
 */
class NBodyPhaseSpace : protected ControlRecord {

public:
  /* constructor */
  #include "ENDFtk/section/6/NBodyPhaseSpace/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the distribution type (the LAW flag)
   */
  static constexpr int LAW() { return 6; }

  /**
   *  @brief Return the total mass of all particles (in neutron mass units)
   */
  double APSX() const { return ControlRecord::C1(); }

  /**
   *  @brief Return the total mass of all particles (in neutron mass units)
   */
  double totalMass() const { return this->APSX(); }

  /**
   *  @brief Return the number of particles
   */
  int NPSX() const { return ControlRecord::N2(); }

  /**
   *  @brief Return the number of particles
   */
  int numberParticles() const { return this->NPSX(); }

  using ControlRecord::NC;
  using ControlRecord::print;
};
