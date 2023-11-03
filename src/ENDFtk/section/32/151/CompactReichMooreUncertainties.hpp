/**
 *  @class
 *  @brief The resonance parameters and uncertainties in the RM representation
 *         (LCOMP = 2)
 *
 *  See ENDF102, section 32.2.3.2 for more information.
 */
class CompactReichMooreUncertainties : protected ListRecord {

  // blatantly stolen from CompactBreitWignerUncertainties
  #include "ENDFtk/section/32/151/CompactBreitWignerUncertainties/src/verifySize.hpp"

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/CompactReichMooreUncertainties/src/generateList.hpp"

  auto column( unsigned int i ) const {

    return ListRecord::list() | ranges::views::drop_exactly( i )
                              | ranges::views::stride( 12 );
  }

public:

  #include "ENDFtk/section/32/151/CompactReichMooreUncertainties/Resonance.hpp"

  /* constructor */
  #include "ENDFtk/section/32/151/CompactReichMooreUncertainties/src/ctor.hpp"

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
   *  @brief Return the value of the l dependent scattering radius
   */
  double APL() const { return ListRecord::C2(); }

  /**
   *  @brief Return the value of the l dependent scattering radius
   */
  double lDependentScatteringRadius() const { return this->APL(); }

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
   *  @brief Return the neutron widths
   */
  auto GN() const { return this->column( 2 ); }

  /**
   *  @brief Return the neutron widths
   */
  auto neutronWidths() const { return this->GN(); }

  /**
   *  @brief Return the gamma widths
   */
  auto GG() const { return this->column( 3 ); }

  /**
   *  @brief Return the gamma widths
   */
  auto gammaWidths() const { return this->GG(); }

  /**
   *  @brief Return the first fission widths
   */
  auto GFA() const { return this->column( 4 ); }

  /**
   *  @brief Return the first fission widths
   */
  auto firstFissionWidths() const { return this->GFA(); }

  /**
   *  @brief Return the second fission widths
   */
  auto GFB() const { return this->column( 5 ); }

  /**
   *  @brief Return the second fission widths
   */
  auto secondFissionWidths() const { return this->GFB(); }

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
  auto DGN() const { return this->column( 8 ); }

  /**
   *  @brief Return the neutron width uncertainties
   */
  auto neutronWidthUncertainties() const { return this->DGN(); }

  /**
   *  @brief Return the gamma width uncertainties
   */
  auto DGG() const { return this->column( 9 ); }

  /**
   *  @brief Return the gamma width uncertainties
   */
  auto gammaWidthUncertainties() const { return this->DGG(); }

  /**
   *  @brief Return the first fission width uncertainties
   */
  auto DGFA() const { return this->column( 10 ); }

  /**
   *  @brief Return the first fission width uncertainties
   */
  auto firstFissionWidthUncertainties() const { return this->DGFA(); }

  /**
   *  @brief Return the second fission width uncertainties
   */
  auto DGFB() const { return this->column( 11 ); }

  /**
   *  @brief Return the second fission width uncertainties
   */
  auto secondFissionWidthUncertainties() const { return this->DGFB(); }

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
