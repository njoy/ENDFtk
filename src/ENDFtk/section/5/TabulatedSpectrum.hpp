/**
 *  @class
 *  @brief Arbitrary tabulated energy distribution (LF=1)
 *
 *  The TabulatedSpectrum class is used to represent the case in which
 *  the energy distribution in an ENDF MF5 section is represented entirely
 *  as a tabulated function.
 *
 *  The tabulated g(E->E') functions are given as tabulated g(E') functions for
 *  fixed E values.
 *
 *  See ENDF102, section 5.1.1.1 and 5.2.1 for more information.
 */
class TabulatedSpectrum {

public:

  #include "ENDFtk/section/5/TabulatedSpectrum/OutgoingEnergyDistribution.hpp"

private:

  /* members */
  InterpolationSequenceRecord< OutgoingEnergyDistribution > data_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/5/TabulatedSpectrum/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int LF() { return 1; }

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  int LAW() const { return this->LF(); }

  /**
   *  @brief Return the number of interpolation ranges on the incident energy
   *         grid
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of incoming energy values
   */
  long NE() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the outgoing energy distributions
   */
  AllRange< OutgoingEnergyDistribution > outgoingDistributions() const {

    return this->data_.records();
  }

  /**
   *  @brief Return the incoming energies
   */
  auto incidentEnergies() const {

    return this->outgoingDistributions()
             | ranges::cpp20::views::transform(
                 [] ( const auto& entry )
                    { return entry.incidentEnergy(); } ); }

  /**
   *  @brief Return interpolation type for each range on the incoming
   *         energy grid
   */
  AllRange< long > interpolants() const {

    return this->data_.tab2().interpolants();
  }

  /**
   *  @brief Return interpolation boundaries for the incoming
   *         energy grid
   */
  AllRange< long > boundaries() const {

    return this->data_.tab2().boundaries();
  }

  /**
   *  @brief Return the number of lines in this MF5 component
   */
  long NC() const { return this->data_.NC(); }

  #include "ENDFtk/section/5/TabulatedSpectrum/src/print.hpp"
};
