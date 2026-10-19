/**
 *  @class
 *  @brief The resonance parameters and variance/covariance data for a given
 *         l value in the SLBW or MLBW representation (LCOMP = 0)
 *
 *  See ENDF102, section 32.2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT LimitedBreitWignerLValue : protected ListRecord {

  /* auxiliary functions */

  static void
  verifySize( int NPL, int NRS ) {

    if ( NPL < 1 ) {

      Log::error( "Encountered empty list" );
      Log::info( "NPL should be larger than zero and equal to 18 * NRS" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NRS value: {}", NRS );
      throw std::exception();
    }

    if ( NRS < 1 ) {

      Log::error( "Encountered illegal NRS value" );
      Log::info( "NRS should be larger than zero" );
      Log::info( "NRS value: {}", NRS );
      throw std::exception();
    }

    if ( NPL != 18 * NRS ) {

      Log::error( "Encountered inconsistent list size" );
      Log::info( "NPL must be equal to 18 * NRS" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NRS value: {}", NRS );
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
                std::vector< double >&& de2,
                std::vector< double >&& dn2,
                std::vector< double >&& dndg,
                std::vector< double >&& dg2,
                std::vector< double >&& dndf,
                std::vector< double >&& dgdf,
                std::vector< double >&& df2,
                std::vector< double >&& djdn,
                std::vector< double >&& djdg,
                std::vector< double >&& djdf,
                std::vector< double >&& dj2 ) {

    unsigned int nrs = energies.size();
    if ( ( spins.size() != nrs ) or ( gt.size() != nrs ) or
         ( gn.size() != nrs ) or ( gg.size() != nrs ) or ( gf.size() != nrs ) or
         ( de2.size() != nrs ) or ( dn2.size() != nrs ) or
         ( dndg.size() != nrs ) or ( dg2.size() != nrs ) or
         ( dndf.size() != nrs ) or ( dgdf.size() != nrs ) or
         ( df2.size() != nrs ) or ( djdn.size() != nrs ) or
         ( djdg.size() != nrs ) or ( djdn.size() != nrs ) or
         ( dj2.size() != nrs ) ) {

      Log::info( "The number of resonances and the resonance parameters are not "
                 "consistent" );
      Log::info( "NRS value: {}", nrs );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "spins.size(): {}", spins.size() );
      Log::info( "gt.size(): {}", gt.size() );
      Log::info( "gn.size(): {}", gn.size() );
      Log::info( "gg.size(): {}", gg.size() );
      Log::info( "gf.size(): {}", gf.size() );
      Log::info( "de2.size(): {}", de2.size() );
      Log::info( "dn2.size(): {}", dn2.size() );
      Log::info( "dndg.size(): {}", dndg.size() );
      Log::info( "dg2.size(): {}", dg2.size() );
      Log::info( "dndf.size(): {}", dndf.size() );
      Log::info( "dgdf.size(): {}", dgdf.size() );
      Log::info( "df2.size(): {}", df2.size() );
      Log::info( "djdn.size(): {}", djdn.size() );
      Log::info( "djdg.size(): {}", djdg.size() );
      Log::info( "djdf.size(): {}", djdf.size() );
      Log::info( "dj2.size(): {}", dj2.size() );
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
      list.push_back( de2[i] );
      list.push_back( dn2[i] );
      list.push_back( dndg[i] );
      list.push_back( dg2[i] );
      list.push_back( dndf[i] );
      list.push_back( dgdf[i] );
      list.push_back( df2[i] );
      list.push_back( djdn[i] );
      list.push_back( djdg[i] );
      list.push_back( djdf[i] );
      list.push_back( dj2[i] );
      list.push_back( 0. );
    }
    return list;
  }

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( i )
                              | std23::views::stride( 18 );
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  LimitedBreitWignerLValue( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifySize( this->NPL(), this->N2() );
  }

public:

  #include "ENDFtk/section/32/151/LimitedBreitWignerLValue/Resonance.hpp"

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] awri       the atomic weight ratio
   *  @param[in] l          the orbital angular momentum value
   *  @param[in] energies   the resonance energies (NRS values)
   *  @param[in] spins      the spin values (NRS values)
   *  @param[in] gt         the total widths (NRS values)
   *  @param[in] gn         the neutron widths (NRS values)
   *  @param[in] gg         the gamma widths (NRS values)
   *  @param[in] gf         the fission widths (NRS values)
   *  @param[in] de2        the energy variances (NRS values)
   *  @param[in] dn2        the neutron width variances (NRS values)
   *  @param[in] dndg       the neutron and gamma width covariances (NRS values)
   *  @param[in] dg2        the gamma width variances (NRS values)
   *  @param[in] dndf       the neutron and fission width covariances (NRS values)
   *  @param[in] dgdf       the gamma and fission width covariances (NRS values)
   *  @param[in] df2        the fission width variances (NRS values)
   *  @param[in] djdn       the spin and neutron width covariances (NRS values)
   *  @param[in] djdg       the spin and gamma width covariances (NRS values)
   *  @param[in] djdf       the spin and fission width covariances (NRS values)
   *  @param[in] df2        the spin variances (NRS values)
   */
  LimitedBreitWignerLValue( double awri, int l,
                            std::vector< double >&& energies,
                            std::vector< double >&& spins,
                            std::vector< double >&& gt,
                            std::vector< double >&& gn,
                            std::vector< double >&& gg,
                            std::vector< double >&& gf,
                            std::vector< double >&& de2,
                            std::vector< double >&& dn2,
                            std::vector< double >&& dndg,
                            std::vector< double >&& dg2,
                            std::vector< double >&& dndf,
                            std::vector< double >&& dgdf,
                            std::vector< double >&& df2,
                            std::vector< double >&& djdn,
                            std::vector< double >&& djdg,
                            std::vector< double >&& djdf,
                            std::vector< double >&& dj2 ) :
    // no try ... catch: exceptions will be handled in the derived class
    LimitedBreitWignerLValue(
            ListRecord( awri, 0., l, 0, energies.size(),
                        generateList( std::move( energies ),
                                      std::move( spins ),
                                      std::move( gt ), std::move( gn ),
                                      std::move( gg ), std::move( gf ),
                                      std::move( de2 ), std::move( dn2 ),
                                      std::move( dndg ), std::move( dg2 ),
                                      std::move( dndf ), std::move( dgdf ),
                                      std::move( df2 ), std::move( djdn ),
                                      std::move( djdg ), std::move( djdf ),
                                      std::move( dj2 ) ) ) ) {}

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
  LimitedBreitWignerLValue( Iterator& it, const Iterator& end, long& lineNumber,
                     int MAT, int MF, int MT ) :
     // no try ... catch: exceptions will be handled in the derived class
    LimitedBreitWignerLValue( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}

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

    using namespace njoy::tools;
    using Chunk = decltype( ( ListRecord::list() | std23::views::chunk( 18 ) )[0] );
    return ListRecord::list() | std23::views::chunk( 18 )
             | std20::views::transform(
                 [] ( Chunk&& chunk ) -> Resonance< Chunk >
                    { return { std::move( chunk ) }; } );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
