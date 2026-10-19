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

  static void
  verifySize( int NPL, int NRSA ) {

    if ( NPL < 1 ) {

      Log::error( "Encountered empty list" );
      Log::info( "NPL should be larger than zero and equal to 12 * NRSA" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NRSA value: {}", NRSA );
      throw std::exception();
    }

    if ( NRSA < 1 ) {

      Log::error( "Encountered illegal NRSA value" );
      Log::info( "NRSA should be larger than zero" );
      Log::info( "NRSA value: {}", NRSA );
      throw std::exception();
    }

    if ( NPL != 12 * NRSA ) {

      Log::error( "Encountered inconsistent list size" );
      Log::info( "NPL must be equal to 12 * NRSA" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NRSA value: {}", NRSA );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( std::vector< double >&& energies,
                std::vector< double >&& spins,
                std::vector< double >&& gt,
                std::vector< double >&& gn,
                std::vector< double >&& gg,
                std::vector< double >&& gf,
                std::vector< double >&& der,
                std::vector< double >&& dgn,
                std::vector< double >&& dgg,
                std::vector< double >&& dgf ) {

    unsigned int nrs = energies.size();
    if ( ( spins.size() != nrs ) or ( gt.size() != nrs ) or
         ( gn.size() != nrs ) or ( gg.size() != nrs ) or ( gf.size() != nrs ) or
         ( der.size() != nrs ) or ( dgn.size() != nrs ) or
         ( dgg.size() != nrs ) or ( dgf.size() != nrs ) ) {

      Log::info( "The number of resonances and the resonance parameters are not "
                 "consistent" );
      Log::info( "NRSA value: {}", nrs );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "spins.size(): {}", spins.size() );
      Log::info( "gt.size(): {}", gt.size() );
      Log::info( "gn.size(): {}", gn.size() );
      Log::info( "gg.size(): {}", gg.size() );
      Log::info( "gf.size(): {}", gf.size() );
      Log::info( "der.size(): {}", der.size() );
      Log::info( "dgn.size(): {}", dgn.size() );
      Log::info( "dgg.size(): {}", dgg.size() );
      Log::info( "dgf.size(): {}", dgf.size() );
      throw std::exception();
    }

    std::vector< double > list;
    for ( unsigned int i = 0; i < nrs; ++i ) {

      list.push_back( energies[i] );
      list.push_back( spins[i] );
      list.push_back( gt[i] );
      list.push_back( gn[i] );
      list.push_back( gg[i] );
      list.push_back( gf[i] );
      list.push_back( der[i] );
      list.push_back( 0. );
      list.push_back( 0. );
      list.push_back( dgn[i] );
      list.push_back( dgg[i] );
      list.push_back( dgf[i] );
    }
    return list;
  }

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( i )
                              | std23::views::stride( 12 );
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  CompactBreitWignerUncertainties( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifySize( this->NPL(), this->N2() );
  }

public:

  #include "ENDFtk/section/32/151/CompactBreitWignerUncertainties/Resonance.hpp"

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  CompactBreitWignerUncertainties() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] awri       the atomic weight ratio
   *  @param[in] qx         the competitive Q value
   *  @param[in] lrx        the competitive width flag
   *  @param[in] energies   the resonance energies (NRSA values)
   *  @param[in] spins      the spin values (NRSA values)
   *  @param[in] gt         the total widths (NRSA values)
   *  @param[in] gn         the neutron widths (NRSA values)
   *  @param[in] gg         the gamma widths (NRSA values)
   *  @param[in] gf         the fission widths (NRSA values)
   *  @param[in] der        the energy uncertainties (NRSA values)
   *  @param[in] dgn        the neutron width uncertainties (NRSA values)
   *  @param[in] dgg        the gamma width uncertainties (NRSA values)
   *  @param[in] dgf        the fission width uncertainties (NRSA values)
   */
  CompactBreitWignerUncertainties( double awri, double qx, bool lrx,
                                   std::vector< double >&& energies,
                                   std::vector< double >&& spins,
                                   std::vector< double >&& gt,
                                   std::vector< double >&& gn,
                                   std::vector< double >&& gg,
                                   std::vector< double >&& gf,
                                   std::vector< double >&& der,
                                   std::vector< double >&& dgn,
                                   std::vector< double >&& dgg,
                                   std::vector< double >&& dgf ) :
    // no try ... catch: exceptions will be handled in the derived class
    CompactBreitWignerUncertainties(
            ListRecord( awri, qx, 0, lrx, energies.size(),
                        generateList( std::move( energies ),
                                      std::move( spins ),
                                      std::move( gt ), std::move( gn ),
                                      std::move( gg ), std::move( gf ),
                                      std::move( der ), std::move( dgn ),
                                      std::move( dgg ), std::move( dgf ) ) ) ) {}

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
  CompactBreitWignerUncertainties( Iterator& it, const Iterator& end, long& lineNumber,
                                   int MAT, int MF, int MT ) :
     // no try ... catch: exceptions will be handled in the derived class
    CompactBreitWignerUncertainties( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}

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
   *  @param[in] unused       placeholder
   */
  template< typename Iterator >
  CompactBreitWignerUncertainties( Iterator& it, const Iterator& end, long& lineNumber,
                                   int MAT, int MF, int MT, int /* unused */ ) :
     // no try ... catch: exceptions will be handled in the derived class
    CompactBreitWignerUncertainties( it, end, lineNumber, MAT, MF, MT ) {}

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

    using namespace njoy::tools;
    using Chunk = decltype( ( ListRecord::list() | std23::views::chunk( 12 ) )[0] );
    return ListRecord::list() | std23::views::chunk( 12 )
             | std20::views::transform(
                 [] ( Chunk&& chunk ) -> Resonance< Chunk >
                    { return { std::move( chunk ) }; } );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
