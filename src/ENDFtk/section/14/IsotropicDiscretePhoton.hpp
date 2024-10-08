/**
 *  @class
 *  @brief The angular distribution for a specific discrete photon is isotropic
 *
 *  See ENDF102, section 14.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT IsotropicDiscretePhoton {

  /* fields */
  double eg_;
  double es_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/14/IsotropicDiscretePhoton/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double ES() const { return this->es_; }

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double levelEnergy() const { return this->ES(); }

  /**
   *  @brief Return the photon energy or the binding energy
   */
  double EG() const { return this->eg_; }

  /**
   *  @brief Return the photon energy or the binding energy
   */
  double photonEnergy() const { return this->EG(); }

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  static constexpr bool LI() { return true; }

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  bool isotropicDistributions() const { return this->LI(); }

  /**
   *  @brief Return the distribution law
   */
  static constexpr int LTT() { return 0; }

  /**
   *  @brief Return the distribution law
   */
  int LAW() const { return this->LTT(); }

  /**
   *  @brief Return the number of lines in this MF12 component
   */
  static constexpr long NC() { return 1; }

  #include "ENDFtk/section/14/IsotropicDiscretePhoton/src/print.hpp"
};
