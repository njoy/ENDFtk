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
          std::variant<
              // LRU=0
              SpecialCase,
              // LRU=1
              SingleLevelBreitWigner, // LRF = 1
              MultiLevelBreitWigner,  // LRF = 2
              ReichMoore,             // LRF = 3
              RMatrixLimited/*,         // LRF = 7
              // LRU=2
              UnresolvedEnergyIndependent,            // LRF = 1, LFW = 0
              UnresolvedEnergyDependentFissionWidths, // LRF = 1, LFW = 1
              UnresolvedEnergyDependent*/ >;            // LRF = 1

private:

  /* fields */
  double el_;
  double eh_;
  int naps_;

  ResonanceParameters parameters_;
  std::optional< ScatteringRadius > scattering_radius_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/ResonanceRange/src/verifyOptions.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/ResonanceRange/src/ctor.hpp"

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
  int LRU() const { return std::visit( [] ( const auto& v ) -> int
                                           { return v.LRU(); },
                                        this->parameters_ ); }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  int type() const { return this->LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  int LRF() const { return std::visit( [] ( const auto& v ) -> int
                                           { return v.LRF(); },
                                        this->parameters_ ); }

  /**
   *  @brief Return the resonance representation
   */
  int representation() const { return this->LRF(); }

  /**
   *  @brief Return whether the scattering radius is energy dependent or not
   */
  bool NRO() const { return bool( this->scattering_radius_ ); }

  /**
   *  @brief Return whether the scattering radius is energy dependent or not
   */
  bool energyDependentScatteringRadius() const { return this->NRO(); }

  /**
   *  @brief Return scattering radius calculation option flag
   */
  int NAPS() const { return this->naps_; }

  /**
   *  @brief Return scattering radius calculation option flag
   */
  int scatteringRadiusCalculationOption() const { return this->NAPS(); }

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

  #include "ENDFtk/section/2/151/ResonanceRange/src/print.hpp"
};
