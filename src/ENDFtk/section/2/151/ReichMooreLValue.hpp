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

  /**
   *  @brief Constructor
   *
   *  @param[in] awri       the atomic weight ratio
   *  @param[in] apl        the l dependent scattering radius
   *  @param[in] l          the orbital angular momentum value
   *  @param[in] energies   the resonance energies (NRS values)
   *  @param[in] spins      the spin values (NRS values)
   *  @param[in] gn         the neutron widths (NRS values)
   *  @param[in] gg         the gamma widths (NRS values)
   *  @param[in] gfa        the first fission widths (NRS values)
   *  @param[in] gfb        the second fission widths (NRS values)
   */
  ReichMooreLValue( double awri, double apl, int l,
                    std::vector< double >&& energies,
                    std::vector< double >&& spins,
                    std::vector< double >&& gn,
                    std::vector< double >&& gg,
                    std::vector< double >&& gfa,
                    std::vector< double >&& gfb )
    try : BreitWignerReichMooreLValueBase( awri, apl, l, false,
                                           std::move( energies ),
                                           std::move( spins ),
                                           std::move( gn ),
                                           std::move( gg ),
                                           std::move( gfa ),
                                           std::move( gfb ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing l value resonance "
                 "parameters in the Reich-Moore representation" );
      throw;
    }

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   */
  template< typename Iterator >
  ReichMooreLValue( Iterator& it, const Iterator& end, long& lineNumber,
                    int MAT, int MF, int MT )
    try : BreitWignerReichMooreLValueBase( it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing l value resonance "
                 "parameters in the Reich-Moore representation" );
      throw;
    }

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
