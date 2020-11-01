/**
 *  @class
 *  @brief Charged particle elastic scattering given as nuclear amplitude
 *         expansion
 *
 *  See ENDF102, section 6.2.6 for more information.
 */
class NuclearAmplitudeExpansion : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/verifyLTP.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/verifySize.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/generateList.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the incident energy
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the representation type
   */
  static constexpr int LTP() { return 1; }

  /**
   *  @brief Return the representation type
   */
  int representation() const { return this->LTP(); }

  /**
   *  @brief Return the number of values in this component
   */
  long NW() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the Legendre order or number of cosine values
   */
  long NL() const { return ListRecord::N2(); }

  /**
   *  @brief Return the interference coefficients (for expanding the nuclear
   *         scattering cross section)
   */
  auto B() const {

    return ListRecord::list()
             | ranges::view::take( this->NW() - 2 * this->NL() - 2 );
  }

  /**
   *  @brief Return the interference coefficients (for expanding the nuclear
   *         scattering cross section)
   */
  auto scatteringCoefficients() const { return this->B(); }

  /**
   *  @brief Return the real component of the interference coefficients
   */
  auto AR() const {

    return ranges::view::drop_exactly( ListRecord::list(),
                                       this->NW() - 2 * this->NL() - 2 )
             | ranges::view::stride( 2 );
  }

  /**
   *  @brief Return the real component of the interference coefficients
   */
  auto realInterferenceCoefficients() const { return this->AR(); }

  /**
   *  @brief Return the imaginary component of the interference coefficients
   */
  auto AI() const {

    return ranges::view::drop_exactly( ListRecord::list(),
                                       this->NW() - 2 * this->NL() - 1 )
             | ranges::view::stride( 2 );
  }

  /**
   *  @brief Return the imaginary component of the interference coefficients
   */
  auto imaginaryInterferenceCoefficients() const { return this->AI(); }

  /**
   *  @brief Return the interference coefficients (for expanding the
   *         nuclear scattering amplitude matrix)
   */
  auto A() const {

    return ranges::view::zip_with(
             [] ( auto real, auto imag )
                { return std::complex< double >( real, imag ); },
             this->realInterferenceCoefficients(),
             this->imaginaryInterferenceCoefficients() );
  }

  /**
   *  @brief Return the interference coefficients (for expanding the
   *         nuclear scattering amplitude matrix)
   */
  auto interferenceCoefficients() const { return this->A(); }

  using ListRecord::NC;
  using ListRecord::print;
};
