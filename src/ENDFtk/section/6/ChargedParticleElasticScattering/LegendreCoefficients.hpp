class LegendreCoefficients : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/verifyLTP.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/verifySize.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/ctor.hpp"

  /* get methods */
  double energy() const { return ListRecord::C2(); }
  static constexpr int LTP() { return 2; }
  long NW() const { return ListRecord::NPL(); }
  long NL() const { return ListRecord::N2(); }

  auto coefficients() const { return ListRecord::list(); }

  using ListRecord::NC;
  using ListRecord::print;
};
