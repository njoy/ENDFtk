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
class ENDFTK_PYTHON_EXPORT LaboratoryAngleEnergy {
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

  /**
   *  @brief Return the number of interpolation regions for the incident
   *         energies
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of interpolation regions for the incident
   *         energies
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of incident energy values
   */
  long NE() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the number of incident energy values
   */
  long numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the interpolants for the incident energy axis
   */
  auto INT() const { return this->data_.tab2().INT(); }

  /**
   *  @brief Return the interpolants for the incident energy axis
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the interpolation region boundaries for the incident
   *         energy axis
   */
  auto NBT() const { return this->data_.tab2().NBT(); }

  /**
   *  @brief Return the interpolation region boundaries for the incident
   *         energy axis
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the angular distributions
   */
  auto angularDistributions() const {

    return this->data_.records();
  }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const {

    return this->angularDistributions()
               | ranges::cpp20::views::transform(
                     [] ( const auto& record )
                        { return record.incidentEnergy(); } );
  }

  /**
  *  @brief Return the incident energy values
   */
  auto incidentEnergies() const { return this->E(); }

  /**
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/6/LaboratoryAngleEnergy/src/print.hpp"
};
