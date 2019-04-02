class NuclearAmplitudeExpansion : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/verifyLTP.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/verifySize.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/generateList.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/ctor.hpp"

  /* get methods */
  double energy() const { return ListRecord::C2(); }
  static constexpr int LTP() { return 1; }
  long NW() const { return ListRecord::NPL(); }
  long NL() const { return ListRecord::N2(); }

  auto scatteringCoefficients() const {
    return ListRecord::list()
             | ranges::view::take( this->NW() - 2 * this->NL() - 2 );
  }
  auto realInterferenceCoefficients() const {
    return ranges::view::drop_exactly( ListRecord::list(), 
                                       this->NW() - 2 * this->NL() - 2 )
             | ranges::view::stride( 2 );
  }
  auto imaginaryInterferenceCoefficients() const {
    return ranges::view::drop_exactly( ListRecord::list(), 
                                       this->NW() - 2 * this->NL() - 1 )
             | ranges::view::stride( 2 );
  }
  auto interferenceCoefficients() const {
    return ranges::view::zip_with(
             [] ( auto real, auto imag )
                { return std::complex< double >( real, imag ); },
             this->realInterferenceCoefficients(),
             this->imaginaryInterferenceCoefficients() );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
