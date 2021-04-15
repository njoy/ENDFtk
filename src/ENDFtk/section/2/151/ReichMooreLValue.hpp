/**
 *  @class
 *  @brief The resonance parameters for a given l value in the Reich-Moore
 *         representation
 *
 *  See ENDF102, section 2.2.1.2 for more information.
 */
class ReichMooreLValue : protected BreitWignerReichMooreLValueBase {

public:

  /* type aliases */
  using Column = BreitWignerReichMooreLValueBase::Column;

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
  Column GN() const { return BreitWignerReichMooreLValueBase::G1(); }

  /**
   *  @brief Return the neutron widths
   */
  Column neutronWidths() const { return this->GN(); }

  /**
   *  @brief Return the gamma widths
   */
  Column GG() const { return BreitWignerReichMooreLValueBase::G2(); }

  /**
   *  @brief Return the gamma widths
   */
  Column gammaWidths() const { return this->GG(); }

  /**
   *  @brief Return the first fission widths
   */
  Column GFA() const { return BreitWignerReichMooreLValueBase::G3(); }

  /**
   *  @brief Return the first fission widths
   */
  Column firstFissionWidths() const { return this->GFA(); }

  /**
   *  @brief Return the second fission widths
   */
  Column GFB() const { return BreitWignerReichMooreLValueBase::G4(); }

  /**
   *  @brief Return the second fission widths
   */
  Column secondFissionWidths() const { return this->GFB(); }

  /**
   *  @brief Return the resonances
   */
  auto resonances() const {

    using Chunk = decltype( BreitWignerReichMooreLValueBase::resonances()[0] );
    return BreitWignerReichMooreLValueBase::resonances()
             | ranges::cpp20::views::transform(
                 [] ( Chunk&& chunk ) -> Resonance< Chunk >
                    { return { std::move( chunk ) }; } );
  }

  using BreitWignerReichMooreLValueBase::NC;
  using BreitWignerReichMooreLValueBase::print;
};
