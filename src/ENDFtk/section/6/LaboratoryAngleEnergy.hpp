/**
 *  @class
 *  @brief The distributions are given in the E,mu,E' ordering
 *
 *  This distribution provides the E,mu,E' ordering of distributions while
 *  the continuum energy-anle representation (law=1) provides the more
 *  traditional E,E',mu ordering. The reference system is supposed to be the
 *  lab system.
 *
 *  See ENDF102, section 6.2.8 for more information.
 */
class LaboratoryAngleEnergy {
public:

  #include "ENDFtk/section/6/LaboratoryAngleEnergy/EnergyDistribution.hpp"
  #include "ENDFtk/section/6/LaboratoryAngleEnergy/AngularDistribution.hpp"

private:
  InterpolationSequenceRecord
    < LaboratoryAngleEnergy::AngularDistribution > data_;

public:
  /* constructor */
  #include "ENDFtk/section/6/LaboratoryAngleEnergy/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the distribution type (the LAW flag)
   */
  static constexpr int LAW() { return 7; }

  long NR() const { return this->data_.tab2().NR(); }
  long NE() const { return this->data_.tab2().NZ(); }

  auto angularDistributions() const { return this->data_.records(); }

  auto interpolants() const { return this->data_.tab2().interpolants(); }
  auto boundaries() const { return this->data_.tab2().boundaries(); }

  /**
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/6/LaboratoryAngleEnergy/src/print.hpp"
};
