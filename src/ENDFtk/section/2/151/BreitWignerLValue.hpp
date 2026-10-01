/**
 *  @class
 *  @brief The resonance parameters for a given l value in the SLBW or MLBW
 *         representation
 *
 *  See ENDF102, section 2.2.1.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT BreitWignerLValue :
  protected BreitWignerReichMooreLValueBase {

public:

  #include "ENDFtk/section/2/151/BreitWignerLValue/Resonance.hpp"

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] awri       the atomic weight ratio
   *  @param[in] qx         the competitive Q value
   *  @param[in] l          the orbital angular momentum value
   *  @param[in] lrx        the competitive width flag
   *  @param[in] energies   the resonance energies (NRS values)
   *  @param[in] spins      the spin values (NRS values)
   *  @param[in] gt         the total widths (NRS values)
   *  @param[in] gn         the neutron widths (NRS values)
   *  @param[in] gg         the gamma widths (NRS values)
   *  @param[in] gf         the fission widths (NRS values)
   */
  BreitWignerLValue( double awri, double qx, int l, bool lrx,
                     std::vector< double >&& energies,
                     std::vector< double >&& spins,
                     std::vector< double >&& gt,
                     std::vector< double >&& gn,
                     std::vector< double >&& gg,
                     std::vector< double >&& gf )
    try : BreitWignerReichMooreLValueBase( awri, qx, l, lrx,
                                           std::move( energies ),
                                           std::move( spins ),
                                           std::move( gt ),
                                           std::move( gn ),
                                           std::move( gg ),
                                           std::move( gf ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing l value resonance "
                 "parameters in the Breit-Wigner representation" );
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
  BreitWignerLValue( Iterator& it, const Iterator& end, long& lineNumber,
                     int MAT, int MF, int MT )
    try : BreitWignerReichMooreLValueBase( it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing l value resonance "
                 "parameters in the Breit-Wigner representation" );
      throw;
    }

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
  bool competitiveWidthFlag() const { return this->LRX(); }

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

    // note: the range-v3 implementation used zip_transform on GT(), GN(), GG() and GF()
    //       but this did not work with the tools implementation (const issues)
    using namespace njoy::tools;
    return BreitWignerReichMooreLValueBase::resonances()
               | std20::views::transform( [] ( auto&& array )
                                             { return array[2] - array[3] - array[4] - array[5]; });
  }

  /**
   *  @brief Return the competitive widths
   */
  auto competitiveWidths() const { return this->GX(); }

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
