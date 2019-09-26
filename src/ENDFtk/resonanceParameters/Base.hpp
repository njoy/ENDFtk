class Base : protected CONT {

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/Base/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the lower energy boundary of the resonance region
   */
  auto EL() const { return CONT::C1(); }

  /**
   *  @brief Return the lower energy boundary of the resonance region
   */
  auto lowerEnergy() const { return this->EL(); }

  /**
   *  @brief Return the upper energy boundary of the resonance region
   */
  auto EH() const { return CONT::C2(); }

  /**
   *  @brief Return the upper energy boundary of the resonance region
   */
  auto upperEnergy() const { return this->EH(); }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  auto LRU() const { return CONT::L1(); }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  auto type() const { return this->LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  auto LRF() const { return CONT::L2(); }

  /**
   *  @brief Return the resonance representation
   */
  auto representation() const { return this->LRF(); }

  /**
   *  @brief Return whether the scattering radius is energy dependent or not
   */
  int NRO() const { return CONT::N1(); }

  /**
   *  @brief Return whether the scattering radius is energy dependent or not
   */
  int energyDependentScatteringRadius() const { return this->NRO(); }

  /**
   *  @brief Return scattering radius calculation option flag
   */
  auto NAPS() const { return CONT::N2(); }

  /**
   *  @brief Return scattering radius calculation option flag
   */
  auto scatteringRadiusCalculationOption() const { return this->NAPS(); }

  using CONT::NC;
  using CONT::print;
};
