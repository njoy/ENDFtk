/**
 *  @class
 *  @brief The resonance parameters for a given l value in the Reich-Moore
 *         representation
 *
 *  See ENDF102, section 2.2.1.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ReichMooreLValue :
  protected BreitWignerReichMooreLValueBase {

public:

  #include "ENDFtk/section/2/151/ReichMooreLValue/Resonance.hpp"

  /* constructor */
  #include "ENDFtk/section/2/151/ReichMooreLValue/src/ctor.hpp"

  using BreitWignerReichMooreLValueBase::AWRI;
  using BreitWignerReichMooreLValueBase::atomicWeightRatio;

  /**
   *  @brief Return the value of the l dependent scattering radius
   */
  double APL() const { return BreitWignerReichMooreLValueBase::C2(); }

  /**
   *  @brief Return the value of the l dependent scattering radius
   */
  double lDependentScatteringRadius() const { return this->APL(); }

  using BreitWignerReichMooreLValueBase::L;
  using BreitWignerReichMooreLValueBase::orbitalMomentum;

  using BreitWignerReichMooreLValueBase::NRS;
  using BreitWignerReichMooreLValueBase::numberResonances;

  using BreitWignerReichMooreLValueBase::ER;
  using BreitWignerReichMooreLValueBase::resonanceEnergies;
  using BreitWignerReichMooreLValueBase::AJ;
  using BreitWignerReichMooreLValueBase::spinValues;

  /**
   *  @brief Return the neutron widths
   */
  auto GN() const { return BreitWignerReichMooreLValueBase::G1(); }

  /**
   *  @brief Return the neutron widths
   */
  auto neutronWidths() const { return this->GN(); }

  /**
   *  @brief Return the gamma widths
   */
  auto GG() const { return BreitWignerReichMooreLValueBase::G2(); }

  /**
   *  @brief Return the gamma widths
   */
  auto gammaWidths() const { return this->GG(); }

  /**
   *  @brief Return the first fission widths
   */
  auto GFA() const { return BreitWignerReichMooreLValueBase::G3(); }

  /**
   *  @brief Return the first fission widths
   */
  auto firstFissionWidths() const { return this->GFA(); }

  /**
   *  @brief Return the second fission widths
   */
  auto GFB() const { return BreitWignerReichMooreLValueBase::G4(); }

  /**
   *  @brief Return the second fission widths
   */
  auto secondFissionWidths() const { return this->GFB(); }

  /**
   *  @brief Return the resonances
   */
  auto resonances() const {

    using namespace njoy::tools;
    using Chunk = decltype( BreitWignerReichMooreLValueBase::resonances()[0] );
    return BreitWignerReichMooreLValueBase::resonances()
             | std20::views::transform(
                 [] ( Chunk&& chunk ) -> Resonance< Chunk >
                    { return { std::move( chunk ) }; } );
  }

  using BreitWignerReichMooreLValueBase::NC;
  using BreitWignerReichMooreLValueBase::print;
};
