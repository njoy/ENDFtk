/**
 *  @class
 *  @brief Discrete two-body scattering data for secondary particles (LAW=2)
 *
 *  The DiscreteTwoBodyScattering class is used to represent the discrete
 *  two-body scattering law=2 data of MF6.
 *
 *  The ContinuumEnergyAngle class is used to represent the two-body angular
 *  distribution law=2 data of MF26. It is similar to the MF6 law=1, but only
 *  supports the LANG=1 option (Legendre coefficients).
 *
 *  See ENDF102, section 26.2.2 for more information.
 */
class DiscreteTwoBodyScattering {

public:

  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/TabulatedDistribution.hpp"

private:

  /* fields */
  InterpolationSequenceRecord< TabulatedDistribution > data_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/26/DiscreteTwoBodyScattering/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the LAW flag
   */
  static constexpr int LAW() { return 2; }

  /**
   *  @brief Return the number of interpolation ranges on the incident
   *         energy axis
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of secondary energy values
   */
  long NE() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the distributions, one for each incident energy
   */
  auto distributions() const { return this->data_.records(); }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const {

    return this->distributions()
               | ranges::cpp20::views::transform(
                     [] ( const auto& record )
                        { return record.incidentEnergy(); } );
  }

  /**
  *  @brief Return the incident energy values
   */
  auto incidentEnergies() const { return this->E(); }

  /**
   *  @brief Return interpolation type for each range on the incident
   *         energy grid
   */
  auto interpolants() const {

    return this->data_.tab2().interpolants();
  }

  /**
   *  @brief Return interpolation boundaries for the incident energy grid
   */
  auto boundaries() const {

    return this->data_.tab2().boundaries();
  }

  /**
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return this->data_.NC(); }

  // taken from MF6
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/src/print.hpp"
};
