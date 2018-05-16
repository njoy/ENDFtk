class NuclearPlusInterference : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/verifyLTP.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/verifySize.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/generateList.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/ctor.hpp"

  /* get methods */
  double energy() const { return ListRecord::C2(); }
  int LTP() const { return ListRecord::L1(); }
  long NW() const { return ListRecord::NPL(); }
  long NL() const { return ListRecord::N2(); }

  auto cosines() const {
    return ListRecord::list() | ranges::view::stride( 2 );
  }
  auto probabilities() const {
    return ranges::view::drop_exactly( ListRecord::list(), 1 )
             | ranges::view::stride( 2 );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
