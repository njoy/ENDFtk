/**
 *  @class
 *  @brief The resonance parameters for a given l value in the SLBW or MLBW
 *         representation
 *
 *  See ENDF102, section 2.2.1.1 for more information.
 */
class BreitWignerLValue : protected BreitWignerReichMooreLValueBase {

public:

  #include "ENDFtk/resonanceParameters/resolved/BreitWignerLValue/Resonance.hpp"

  /* constructor */
  #include "ENDFtk/resonanceParameters/resolved/BreitWignerLValue/src/ctor.hpp"

  using BreitWignerReichMooreLValueBase::AWRI;
  using BreitWignerReichMooreLValueBase::atomicWeightRatio;

  /**
   *  @brief Return the Q value of the competitive reaction
   */
  double QX() const { return BreitWignerReichMooreLValueBase::C2(); }

  /**
   *  @brief Return the Q value of the competitive reaction
   */
  double competitiveQValue() const { return this->QX(); }

  using BreitWignerReichMooreLValueBase::L;
  using BreitWignerReichMooreLValueBase::orbitalMomentum;

  /**
   *  @brief Return the competitive width flag
   */
  bool LRX() const { return BreitWignerReichMooreLValueBase::L2(); }

  /**
   *  @brief Return the competitive width flag
   */
  bool competitiveWidth() const { return this->LRX(); }

  using BreitWignerReichMooreLValueBase::NRS;
  using BreitWignerReichMooreLValueBase::numberResonances;

  using BreitWignerReichMooreLValueBase::ER;
  using BreitWignerReichMooreLValueBase::resonanceEnergies;
  using BreitWignerReichMooreLValueBase::AJ;
  using BreitWignerReichMooreLValueBase::spinValues;

  /**
   *  @brief Return the total widths
   */
  auto GT() const { return BreitWignerReichMooreLValueBase::G1(); }

  /**
   *  @brief Return the total widths
   */
  auto totalWidths() const { return this->GT(); }

  /**
   *  @brief Return the neutron widths
   */
  auto GN() const { return BreitWignerReichMooreLValueBase::G2(); }

  /**
   *  @brief Return the neutron widths
   */
  auto neutronWidths() const { return this->GN(); }

  /**
   *  @brief Return the gamma widths
   */
  auto GG() const { return BreitWignerReichMooreLValueBase::G3(); }

  /**
   *  @brief Return the gamma widths
   */
  auto gammaWidths() const { return this->GG(); }

  /**
   *  @brief Return the fission widths
   */
  auto GF() const { return BreitWignerReichMooreLValueBase::G4(); }

  /**
   *  @brief Return the first fission widths
   */
  auto fissionWidths() const { return this->GF(); }

  /**
   *  @brief Return the competitive widths
   */
  auto GX() const {

    return ranges::view::zip_with( 
             [] ( double gt, double gn, double gg, double gf )
                { return gt - gn - gg - gf; },
             this->GT(), this->GN(), this->GG(), this->GF() );
  }

  /**
   *  @brief Return the competitive widths
   */
  auto competitiveWidths() const { return this->GX(); }

  /**
   *  @brief Return the resonances
   */
  auto resonances() const {

    using Chunk = decltype( BreitWignerReichMooreLValueBase::resonances()[0] );
    return BreitWignerReichMooreLValueBase::resonances()
             | ranges::view::transform(
                 [] ( Chunk&& chunk ) -> Resonance< Chunk >
                    { return { std::move( chunk ) }; } );
  }

  using BreitWignerReichMooreLValueBase::NC;
  using BreitWignerReichMooreLValueBase::print;
};

