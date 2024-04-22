/**
 *  @class
 *  @brief Continuum energy-angle data for secondary particles (LAW=1)
 *
 *  The ContinuumEnergyAngle class is used to represent the continuum
 *  energy-angle law=1 data of MF26. It is similar to the MF6 law=1, but only
 *  supports the LANG=1 option (Legendre coefficients). In addition, only NA=0
 *  is allowed but we do not enforce that restriction.
 *
 *  See ENDF102, section 26.2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT ContinuumEnergyAngle {

public:

  // components taken from MF6
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Base.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients.hpp"

private:

  /* fields */
  InterpolationSequenceRecord< LegendreCoefficients > data_;

  /* auxiliary functions */
  #include "ENDFtk/section/26/ContinuumEnergyAngle/src/readSequence.hpp"
  #include "ENDFtk/section/26/ContinuumEnergyAngle/src/verifyLANG.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/26/ContinuumEnergyAngle/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the LAW flag
   */
  static constexpr int LAW() { return 1; }

  /**
   *  @brief Return the LANG flag for the data representation type
   */
  int LANG() const { return this->data_.tab2().L1(); }

  /**
   *  @brief Return the interpolation scheme for secondary energies
   */
  int LEP() const { return this->data_.tab2().L2(); }

  /**
   *  @brief Return the interpolation scheme for secondary energies
   */
  int interpolationScheme() const { return this->LEP(); }

  /**
   *  @brief Return the number of interpolation regions on the incident
   *         energy axis
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of interpolation regions on the incident
   *         energy axis
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
   *  @brief Return the subsections, one for each incident energy
   */
  auto distributions() const {

    return this->data_.records();
  }

  /**
   *  @brief Return interpolation type for each region on the incident
   *         energy grid
   */
  auto INT() const { return this->data_.tab2().INT(); }

  /**
   *  @brief Return interpolation type for each region on the incident
   *         energy grid
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return interpolation boundaries for the incident energy grid
   */
  auto NBT() const { return this->data_.tab2().NBT(); }

  /**
   *  @brief Return interpolation boundaries for the incident energy grid
   */
  auto boundaries() const { return this->NBT(); }

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
   *  @brief Return the number of lines in this MF26 component
   */
  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/print.hpp" // taken from MF6
};
