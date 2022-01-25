/**
 *  @class
 *  @brief Short-range Breit-Wigner resonance parameters and covariance data
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ShortRangeBreitWignerBlock :
  protected ShortRangeBreitWignerReichMooreBlockBase {

public:

  // reusing the Breit-Wigner resonance interface
  #include "ENDFtk/section/2/151/BreitWignerLValue/Resonance.hpp"

  /* constructor */
  #include "ENDFtk/section/32/151/ShortRangeBreitWignerBlock/src/ctor.hpp"

  using ShortRangeBreitWignerReichMooreBlockBase::AWRI;
  using ShortRangeBreitWignerReichMooreBlockBase::atomicWeightRatio;
  using ShortRangeBreitWignerReichMooreBlockBase::MPAR;
  using ShortRangeBreitWignerReichMooreBlockBase::numberParametersWithCovariances;
  using ShortRangeBreitWignerReichMooreBlockBase::NRB;
  using ShortRangeBreitWignerReichMooreBlockBase::numberResonances;

  using ShortRangeBreitWignerReichMooreBlockBase::ER;
  using ShortRangeBreitWignerReichMooreBlockBase::resonanceEnergies;
  using ShortRangeBreitWignerReichMooreBlockBase::AJ;
  using ShortRangeBreitWignerReichMooreBlockBase::spinValues;

  /**
   *  @brief Return the total widths
   */
  auto GT() const { return ShortRangeBreitWignerReichMooreBlockBase::G1(); }

  /**
   *  @brief Return the total widths
   */
  auto totalWidths() const { return this->GT(); }

  /**
   *  @brief Return the neutron widths
   */
  auto GN() const { return ShortRangeBreitWignerReichMooreBlockBase::G2(); }

  /**
   *  @brief Return the neutron widths
   */
  auto neutronWidths() const { return this->GN(); }

  /**
   *  @brief Return the gamma widths
   */
  auto GG() const { return ShortRangeBreitWignerReichMooreBlockBase::G3(); }

  /**
   *  @brief Return the gamma widths
   */
  auto gammaWidths() const { return this->GG(); }

  /**
   *  @brief Return the fission widths
   */
  auto GF() const { return ShortRangeBreitWignerReichMooreBlockBase::G4(); }

  /**
   *  @brief Return the first fission widths
   */
  auto fissionWidths() const { return this->GF(); }

  /**
   *  @brief Return the resonances
   */
  auto resonances() const {

    using Chunk = decltype( ShortRangeBreitWignerReichMooreBlockBase::resonances()[0] );
    return ShortRangeBreitWignerReichMooreBlockBase::resonances()
             | ranges::cpp20::views::transform(
                 [] ( Chunk&& chunk ) -> Resonance< Chunk >
                    { return { std::move( chunk ) }; } );
  }

  using ShortRangeBreitWignerReichMooreBlockBase::covarianceMatrixOrder;
  using ShortRangeBreitWignerReichMooreBlockBase::NVS;
  using ShortRangeBreitWignerReichMooreBlockBase::numberValues;
  using ShortRangeBreitWignerReichMooreBlockBase::covarianceMatrix;

  //! @todo provide convenience interface for the covariance data

  using ShortRangeBreitWignerReichMooreBlockBase::NC;
  using ShortRangeBreitWignerReichMooreBlockBase::print;
};
