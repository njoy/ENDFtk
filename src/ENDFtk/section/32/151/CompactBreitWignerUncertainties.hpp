/**
 *  @class
 *  @brief The resonance parameters and uncertainties in the SLBW or MLBW
 *         representation (LCOMP = 2)
 *
 *  See ENDF102, section 32.2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT CompactBreitWignerUncertainties : 
  protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/CompactBreitWignerUncertainties/src/verifySize.hpp"
  #include "ENDFtk/section/32/151/CompactBreitWignerUncertainties/src/generateList.hpp"

  auto column( unsigned int i ) const {

    return ListRecord::list() | ranges::views::drop_exactly( i )
                              | ranges::views::stride( 12 );
  }

public:

  #include "ENDFtk/section/32/151/CompactBreitWignerUncertainties/Resonance.hpp"

  /* constructor */
  #include "ENDFtk/section/32/151/CompactBreitWignerUncertainties/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double AWRI() const { return ListRecord::C1(); }

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double atomicWeightRatio() const { return this->AWRI(); }

  /**
   *  @brief Return the Q value of the competitive reaction
   */
  double QX() const { return ListRecord::C2(); }

  /**
   *  @brief Return the Q value of the competitive reaction
   */
  double competitiveQValue() const { return this->QX(); }

  /**
   *  @brief Return the competitive width flag
   */
  bool LRX() const { return ListRecord::L2(); }

  /**
   *  @brief Return the competitive width flag
   */
  bool competitiveWidthFlag() const { return this->LRX(); }

  /**
   *  @brief Return the number of resonances
   */
  int NRSA() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of resonances
   */
  int numberResonances() const { return this->NRSA(); }

  /**
   *  @brief Return the resonance energies
   */
  auto ER() const { return this->column( 0 ); }

  /**
  *  @brief Return the resonance energies
   */
  auto resonanceEnergies() const { return this->ER(); }

  /**
   *  @brief Return the spin values
   */
  auto AJ() const { return this->column( 1 ); }

  /**
  *  @brief Return the spin values
   */
  auto spinValues() const { return this->AJ(); }

  /**
   *  @brief Return the total widths
   */
  auto GT() const { return this->column( 2 ); }

  /**
   *  @brief Return the total widths
   */
  auto totalWidths() const { return this->GT(); }

  /**
   *  @brief Return the neutron widths
   */
  auto GN() const { return this->column( 3 ); }

  /**
   *  @brief Return the neutron widths
   */
  auto neutronWidths() const { return this->GN(); }

  /**
   *  @brief Return the gamma widths
   */
  auto GG() const { return this->column( 4 ); }

  /**
   *  @brief Return the gamma widths
   */
  auto gammaWidths() const { return this->GG(); }

  /**
   *  @brief Return the fission widths
   */
  auto GF() const { return this->column( 5 ); }

  /**
   *  @brief Return the first fission widths
   */
  auto fissionWidths() const { return this->GF(); }

  /**
   *  @brief Return the resonance energy uncertainties
   */
  auto DER() const { return this->column( 6 ); }

  /**
   *  @brief Return the resonance energy uncertainties
   */
  auto resonanceEnergyUncertainties() const { return this->DER(); }

  /**
   *  @brief Return the neutron width uncertainties
   */
  auto DGN() const { return this->column( 9 ); }

  /**
   *  @brief Return the neutron width uncertainties
   */
  auto neutronWidthUncertainties() const { return this->DGN(); }

  /**
   *  @brief Return the gamma width uncertainties
   */
  auto DGG() const { return this->column( 10 ); }

  /**
   *  @brief Return the gamma width uncertainties
   */
  auto gammaWidthUncertainties() const { return this->DGG(); }

  /**
   *  @brief Return the fission width uncertainties
   */
  auto DGF() const { return this->column( 11 ); }

  /**
   *  @brief Return the fission width uncertainties
   */
  auto fissionWidthUncertainties() const { return this->DGF(); }

  /**
   *  @brief Return the resonances
   */
  auto resonances() const {

    using Chunk = decltype( ( ListRecord::list() | ranges::views::chunk(12) )[0] );
    return ListRecord::list() | ranges::views::chunk(12)
             | ranges::cpp20::views::transform(
                 [] ( Chunk&& chunk ) -> Resonance< Chunk >
                    { return { std::move( chunk ) }; } );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
