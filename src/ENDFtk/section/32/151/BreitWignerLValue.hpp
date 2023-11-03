/**
 *  @class
 *  @brief The resonance parameters and variance/covariance data for a given
 *         l value in the SLBW or MLBW representation (LCOMP = 0)
 *
 *  See ENDF102, section 32.2.1 for more information.
 */
class BreitWignerLValue : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/BreitWignerLValue/src/verifySize.hpp"
  #include "ENDFtk/section/32/151/BreitWignerLValue/src/generateList.hpp"

  auto column( unsigned int i ) const {

    return ListRecord::list() | ranges::views::drop_exactly( i )
                              | ranges::views::stride( 18 );
  }

public:

  #include "ENDFtk/section/32/151/BreitWignerLValue/Resonance.hpp"

  /* constructor */
  #include "ENDFtk/section/32/151/BreitWignerLValue/src/ctor.hpp"

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
   *  @brief Return the value of the orbital momentum l
   */
  int L() const { return ListRecord::L1(); }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int orbitalMomentum() const { return this->L(); }

  /**
   *  @brief Return the number of resonances for this l value
   */
  int NRS() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of resonances for this l value
   */
  int numberResonances() const { return this->NRS(); }

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
   *  @brief Return the resonance energy variances
   */
  auto DE2() const { return this->column( 6 ); }

  /**
   *  @brief Return the resonance energy variances
   */
  auto resonanceEnergyVariances() const { return this->DE2(); }

  /**
   *  @brief Return the neutron width variances
   */
  auto DN2() const { return this->column( 7 ); }

  /**
   *  @brief Return the neutron width variances
   */
  auto neutronWidthVariances() const { return this->DN2(); }

  /**
   *  @brief Return the neutron and gamma width covariances
   */
  auto DNDG() const { return this->column( 8 ); }

  /**
   *  @brief Return the neutron and gamma width covariances
   */
  auto neutronAndGammaWidthCovariances() const { return this->DNDG(); }

  /**
   *  @brief Return the gamma width variances
   */
  auto DG2() const { return this->column( 9 ); }

  /**
   *  @brief Return the gamma width variances
   */
  auto gammaWidthVariances() const { return this->DG2(); }

  /**
   *  @brief Return the neutron and fission width covariances
   */
  auto DNDF() const { return this->column( 10 ); }

  /**
   *  @brief Return the neutron and fission width covariances
   */
  auto neutronAndFissionWidthCovariances() const { return this->DNDF(); }

  /**
   *  @brief Return the gamma and fission width covariances
   */
  auto DGDF() const { return this->column( 11 ); }

  /**
   *  @brief Return the neutron and fission width covariances
   */
  auto gammaAndFissionWidthCovariances() const { return this->DGDF(); }

  /**
   *  @brief Return the fission width variances
   */
  auto DF2() const { return this->column( 12 ); }

  /**
   *  @brief Return the fission width variances
   */
  auto fissionWidthVariances() const { return this->DF2(); }

  /**
   *  @brief Return the spin and neutron width covariances
   */
  auto DJDN() const { return this->column( 13 ); }

  /**
   *  @brief Return the spin and neutron width covariances
   */
  auto spinAndNeutronWidthCovariances() const { return this->DJDN(); }

  /**
   *  @brief Return the spin and gamma width covariances
   */
  auto DJDG() const { return this->column( 14 ); }

  /**
   *  @brief Return the spin and gamma width covariances
   */
  auto spinAndGammaWidthCovariances() const { return this->DJDG(); }

  /**
   *  @brief Return the spin and fission width covariances
   */
  auto DJDF() const { return this->column( 15 ); }

  /**
   *  @brief Return the spin and fission width covariances
   */
  auto spinAndFissionWidthCovariances() const { return this->DJDF(); }

  /**
   *  @brief Return the spin variances
   */
  auto DJ2() const { return this->column( 16 ); }

  /**
   *  @brief Return the spin variances
   */
  auto spinVariances() const { return this->DJ2(); }

  /**
   *  @brief Return the resonances
   */
  auto resonances() const {

    using Chunk = decltype( ( ListRecord::list() | ranges::views::chunk(18) )[0] );
    return ListRecord::list() | ranges::views::chunk(18)
             | ranges::cpp20::views::transform(
                 [] ( Chunk&& chunk ) -> Resonance< Chunk >
                    { return { std::move( chunk ) }; } );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
