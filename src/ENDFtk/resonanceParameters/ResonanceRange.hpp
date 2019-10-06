/**
 *  @class
 *  @brief A resonance energy range with parameters
 *
 *  The ResonanceRange class is used to represent a resonance range (resolved
 *  or unresolved) from MF2/MT151.
 *
 *  See ENDF102, section 2.1 for more information.
 */
class ResonanceRange {

public:

  using ResonanceParameters =
          std::variant< // LRU=0
/*                        SpecialCase,
                        // LRU=1
                        resolved::MLBW,            // LRF = 2
                        resolved::SLBW,            // LRF = 1
                        resolved::ReichMoore, */     // LRF = 3
                        resolved::LimitedRMatrix/*,  // LRF = 7
                        // LRU=2
                        unresolved::EnergyIndependent,
                        unresolved::EnergyDependentFissionWidths,
                        unresolved::EnergyDependent*/>;

private:

  /* fields */
  double el_;
  double eh_;
  int naps_;

  std::optional< ScatteringRadius > scattering_radius_;
  ResonanceParameters parameters_;

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/Base/src/verifyOptions.hpp"
  #include "ENDFtk/resonanceParameters/Base/src/readScatteringRadius.hpp"
  #include "ENDFtk/resonanceParameters/Base/src/readParameters.hpp"

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/Base/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the lower energy boundary of the resonance region
   */
  auto EL() const { return this->el_; }

  /**
   *  @brief Return the lower energy boundary of the resonance region
   */
  auto lowerEnergy() const { return this->EL(); }

  /**
   *  @brief Return the upper energy boundary of the resonance region
   */
  auto EH() const { return this->eh_; }

  /**
   *  @brief Return the upper energy boundary of the resonance region
   */
  auto upperEnergy() const { return this->EH(); }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  auto LRU() const { return std::visit( [] ( const auto& v ) -> int
                                           { return v.LRU(); },
                                        this->parameters_ ); }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  auto type() const { return this->LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  auto LRF() const { return return std::visit( [] ( const auto& v ) -> int
                                                  { return v.LRF(); },
                                               this->parameters_ ); }

  /**
   *  @brief Return the resonance representation
   */
  auto representation() const { return this->LRF(); }

  /**
   *  @brief Return whether the scattering radius is energy dependent or not
   */
  bool NRO() const { return this->scattering_radius_; }

  /**
   *  @brief Return whether the scattering radius is energy dependent or not
   */
  bool energyDependentScatteringRadius() const { return this->NRO(); }

  /**
   *  @brief Return scattering radius calculation option flag
   */
  auto NAPS() const { return this->naps_; }

  /**
   *  @brief Return scattering radius calculation option flag
   */
  auto scatteringRadiusCalculationOption() const { return this->NAPS(); }

  /**
   *  @brief Return optional scattering radius
   */
  const auto& scatteringRadius() const { return this->scattering_radius_; }

  /**
   *  @brief Return the resonance parameters
   */

  const auto& parameters() const { return this->parameters_; }
  /**
   *  @brief Return the number of lines in this MF2/MT151 component
   */
  long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                              { return v.NC(); },
                                           this->parameters_ ); }

  #include "ENDFtk/resonanceParameters/ResonanceRange/src/print.hpp"
};
