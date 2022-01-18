/**
 *  @class
 *  @brief A resonance energy range with parameters and covariance data
 *
 *  See ENDF102, section 32.1 for more information.
 */
class ResonanceRange {

public:

  /* type aliases */
  using OptionalScatteringRadiusCovariances = std::optional< ScatteringRadiusCovariances >;

  using ResonanceParameters =
          std::variant<
              LimitedSingleLevelBreitWigner, // LCOMP = 0, LRF = 1
              LimitedMultiLevelBreitWigner   // LCOMP = 0, LRF = 2
              >;

private:

  /* fields */
  double el_;
  double eh_;
  int naps_;

  ResonanceParameters parameters_;
  OptionalScatteringRadiusCovariances scattering_radius_;

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/ResonanceRange/src/verifyOptions.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/ResonanceRange/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the lower energy boundary of the resonance region
   */
  double EL() const { return this->el_; }

  /**
   *  @brief Return the lower energy boundary of the resonance region
   */
  double lowerEnergy() const { return this->EL(); }

  /**
   *  @brief Return the upper energy boundary of the resonance region
   */
  double EH() const { return this->eh_; }

  /**
   *  @brief Return the upper energy boundary of the resonance region
   */
  double upperEnergy() const { return this->EH(); }

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
   *  @brief Return the average fission flag
   */
  bool LFW() const { return std::visit( [] ( const auto& v ) -> bool
                                          { return v.LFW(); },
                                        this->parameters_ ); }

  /**
   *  @brief Return the average fission flag
   */
  bool averageFissionWidthFlag() const { return this->LFW(); }

  /**
   *  @brief Return the average fission flag
   */
  bool LCOMP() const { return std::visit( [] ( const auto& v ) -> bool
                                             { return v.LFW(); },
                                          this->parameters_ ); }

  /**
   *  @brief Return the covariance representation
   */
  int covarianceRepresentation() const { return this->LCOMP(); }

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
  const OptionalScatteringRadiusCovariances& scatteringRadius() const {

    return this->scattering_radius_;
  }

  /**
   *  @brief Return the resonance parameters
   */
  const ResonanceParameters& parameters() const { return this->parameters_; }

  #include "ENDFtk/section/32/151/ResonanceRange/src/NC.hpp"
  #include "ENDFtk/section/32/151/ResonanceRange/src/print.hpp"
};
