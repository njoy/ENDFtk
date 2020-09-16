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
  #include "ENDFtk/section/6/ContinuumEnergyAngle/EqualProbabilityBins.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Tabulated.hpp"

  using Variant = std::variant< LegendreCoefficients, // LANG=1
                                KalbachMann,          // LANG=2
                                EqualProbabilityBins, // LANG=3
                                Tabulated >;          // LANG=11-15

private:

  /* fields */
  InterpolationSequenceRecord< Variant > data_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/readSequence.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/verifyLANG.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the LAW flag for continuum energy-angle data
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
   *  @brief Return the number of interpolation ranges used
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of secondary energy values
   */
  long NE() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the subsections, one for each secondary energy
   */
  auto subsections() const { return this->data_.records(); }

  /**
   *  @brief Return the interpolation type for each interpolation region
   */
  auto interpolants() const { return this->data_.tab2().interpolants(); }

  /**
   *  @brief Return the boundaries for each interpolation region
   */
  auto boundaries() const { return this->data_.tab2().boundaries(); }

  /**
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/6/ContinuumEnergyAngle/src/print.hpp"
};
