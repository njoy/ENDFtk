/**
 *  @class
 *  @brief Continuum energy-angle data for secondary particles (LAW=1)
 *
 *  The ContinuumEnergyAngle class is used to represent the continuum
 *  energy-angle law=1 data of MF6.
 *
 *  See ENDF102, section 6.2.3 for more information.
 */
class ContinuumEnergyAngle {

public:

  #include "ENDFtk/section/6/ContinuumEnergyAngle/Base.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/ThermalScatteringData.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/TabulatedDistribution.hpp"

  using Variant = std::variant< LegendreCoefficients,    // LANG=1
                                KalbachMann,             // LANG=2
                                ThermalScatteringData,   // LANG=3
                                TabulatedDistribution >; // LANG=11-15

private:

  /* fields */
  InterpolationSequenceRecord< Variant > data_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/readSequence.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/verifyLANG.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/ctor.hpp"

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
   *  @brief Return the number of interpolation ranges on the incident
   *         energy axis
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of incident energy values
   */
  long NE() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the subsections, one for each incident energy
   */
  AllRange< Variant > distributions() const {

    return this->data_.records();
  }

  /**
   *  @brief Return interpolation type for each range on the incident
   *         energy grid
   */
  AllRange< long > interpolants() const {

    return this->data_.tab2().interpolants();
  }

  /**
   *  @brief Return interpolation boundaries for the incident energy grid
   */
  AllRange< long > boundaries() const {

    return this->data_.tab2().boundaries();
  }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const {

    return this->distributions()
               | ranges::cpp20::views::transform(
                  [] ( const auto& variant )
                     { return std::visit( [] ( const auto& record )
                                             { return record.incidentEnergy(); },
                                          variant ); } );
  }

  /**
  *  @brief Return the incident energy values
   */
  auto incidentEnergies() const { return this->E(); }

  /**
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/print.hpp"
};
