/**
 *  @class
 *  @brief The angular distribution is isotropic in CM and no data is given
 *
 *  See ENDF102, section 6.2.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT IsotropicDiscreteEmission : protected NoLawDataGiven {

public:

  /* methods */

  /**
   *  @brief Return the distribution type (the LAW flag)
   */
  static constexpr int LAW() { return 3; }

  using NoLawDataGiven::NC;
  using NoLawDataGiven::print;
};
