/**
 *  @class
 *  @brief Particle pair information for the R-matrix limited uncertainty data
 *         (LCOMP = 2)
 *
 *  The ParticlePairs class here is very similar to the MF2 MT151 version but
 *  it contains one additional parameter: NJSX.
 *
 *  See ENDF102, section 32.2.3.3 for more information - if you don't value
 *  your sanity.
 */
class ENDFTK_PYTHON_EXPORT ParticlePairs : protected ListRecord {

  /* auxiliary functions */

  static std::vector< double >
  generateList( std::vector< double >&& ma, std::vector< double >&& mb,
                std::vector< double >&& za, std::vector< double >&& zb,
                std::vector< double >&& ia, std::vector< double >&& ib,
                std::vector< double >&& q, std::vector< int >&& pnt,
                std::vector< int >&& shf, std::vector< int >&& mt,
                std::vector< double >&& pa, std::vector< double >&& pb ) {

    unsigned int npp = ma.size();
    if ( ( mb.size() != npp ) or
         ( za.size() != npp ) or ( zb.size() != npp ) or
         ( ia.size() != npp ) or ( ib.size() != npp ) or
         ( q.size() != npp ) or ( pnt.size() != npp ) or
         ( shf.size() != npp ) or ( mt.size() != npp ) or
         ( pa.size() != npp ) or ( pb.size() != npp ) ) {

      Log::info( "The number of particle pairs and the particle pair is not "
                 "consistent" );
      Log::info( "NPP value: {}", npp );
      Log::info( "ma.size(): {}", ma.size() );
      Log::info( "mb.size(): {}", mb.size() );
      Log::info( "za.size(): {}", za.size() );
      Log::info( "zb.size(): {}", zb.size() );
      Log::info( "ia.size(): {}", ia.size() );
      Log::info( "ib.size(): {}", ib.size() );
      Log::info( "q.size(): {}", q.size() );
      Log::info( "pnt.size(): {}", pnt.size() );
      Log::info( "shf.size(): {}", shf.size() );
      Log::info( "mt.size(): {}", mt.size() );
      Log::info( "pa.size(): {}", pa.size() );
      Log::info( "pb.size(): {}", pb.size() );
      throw std::exception();
    }

    std::vector< double > list;
    for ( unsigned int i = 0; i < npp; ++i ) {

      list.push_back( ma[i] );
      list.push_back( mb[i] );
      list.push_back( za[i] );
      list.push_back( zb[i] );
      list.push_back( ia[i] );
      list.push_back( ib[i] );
      list.push_back( q[i] );
      list.push_back( pnt[i] );
      list.push_back( shf[i] );
      list.push_back( mt[i] );
      list.push_back( pa[i] );
      list.push_back( pb[i] );
    }
    return list;
  }

  static void
  verifySize( int NPL, int NPP ) {

    if ( NPL < 1 ) {

      Log::error( "Encountered empty list" );
      Log::info( "NPL should be larger than zero and equal to 12 * NPP" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NPP value: {}", NPP );
      throw std::exception();
    }

    if ( NPP < 1 ) {

      Log::error( "Encountered illegal NPP value" );
      Log::info( "NPP should be larger than zero" );
      Log::info( "NPP value: {}", NPP );
      throw std::exception();
    }

    if ( NPL / 12. != NPP ) {

      Log::error( "Encountered inconsistent list size" );
      Log::info( "NPL must be equal to 12 * NPP" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NPP value: {}", NPP );
      throw std::exception();
    }
  }

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( i )
             | std23::views::stride( 12 );
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  ParticlePairs( ListRecord&& list ) : ListRecord( std::move( list ) ) {

    verifySize( this->NPL(), this->L1() );
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ParticlePairs() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] njsx    the number of spin groups included in the uncertainty
   *                     data
   *  @param[in] ma      the mass of the first particle in each particle pair
   *  @param[in] mb      the mass of the first particle in each particle pair
   *  @param[in] za      the charge of the first particle in each particle pair
   *  @param[in] zb      the charge of the first particle in each particle pair
   *  @param[in] ia      the spin of the first particle in each particle pair
   *  @param[in] ib      the spin of the first particle in each particle pair
   *  @param[in] pa      the parity of the first particle in each particle pair
   *  @param[in] pb      the parity of the first particle in each particle pair
   *  @param[in] q       the mass of the first particle in each particle pair
   *  @param[in] pnt     the mass of the first particle in each particle pair
   *  @param[in] shf     the charge of the first particle in each particle pair
   *  @param[in] mt      the charge of the first particle in each particle pair
   */
  ParticlePairs( int njsx,
                 std::vector< double >&& ma, std::vector< double >&& mb,
                 std::vector< double >&& za, std::vector< double >&& zb,
                 std::vector< double >&& ia, std::vector< double >&& ib,
                 std::vector< double >&& pa, std::vector< double >&& pb,
                 std::vector< double >&& q, std::vector< int >&& pnt,
                 std::vector< int >&& shf, std::vector< int >&& mt )
    try : ParticlePairs(
            ListRecord( 0., 0., ma.size(), njsx, 2 * ma.size(),
                        generateList( std::move( ma ), std::move( mb ),
                                      std::move( za ), std::move( zb ),
                                      std::move( ia ), std::move( ib ),
                                      std::move( q ), std::move( pnt ),
                                      std::move( shf ), std::move( mt ),
                                      std::move( pa ), std::move( pb ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing particle pairs" );
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
  ParticlePairs( Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT )
    try : ParticlePairs( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing particle pairs" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the number of spin groups for which resonance parameters
   *         are given
   */
  int NJSX() const { return ListRecord::L2(); }

  /**
   *  @brief Return the number of spin groups for which resonance parameters
   *         are given
   */
  int numberSpinGroups() const { return this->NJSX(); }

  /**
   *  @brief Return the number of particle pairs
   */
  unsigned int NPP() const { return ListRecord::NPL() / 12; }

  /**
   *  @brief Return the number of particle pairs
   */
  unsigned int numberParticlePairs() const { return this->NPP(); }

  /**
   *  @brief Return the mass of the first particle in each particle pair
   */
  auto MA() const { return ParticlePairs::column( 0 ); }

  /**
   *  @brief Return the mass of the first particle in each particle pair
   */
  auto massParticleA() const { return this->MA(); }

  /**
   *  @brief Return the mass of the second particle in each particle pair
   */
  auto MB() const { return ParticlePairs::column( 1 ); }

  /**
   *  @brief Return the mass of the second particle in each particle pair
   */
  auto massParticleB() const { return this->MB(); }

  /**
   *  @brief Return the charge of the first particle in each particle pair
   */
  auto ZA() const { return ParticlePairs::column( 2 ); }

  /**
   *  @brief Return the charge of the first particle in each particle pair
   */
  auto chargeParticleA() const { return this->ZA(); }

  /**
   *  @brief Return the charge of the second particle in each particle pair
   */
  auto ZB() const { return ParticlePairs::column( 3 ); }

  /**
   *  @brief Return the charge of the second particle in each particle pair
   */
  auto chargeParticleB() const { return this->ZB(); }

  /**
   *  @brief Return the spin of the first particle in each particle pair
   */
  auto IA() const { return ParticlePairs::column( 4 ); }

  /**
   *  @brief Return the spin of the first particle in each particle pair
   */
  auto spinParticleA() const { return this->IA(); }

  /**
   *  @brief Return the spin of the second particle in each particle pair
   */
  auto IB() const { return ParticlePairs::column( 5 ); }

  /**
   *  @brief Return the spin of the second particle in each particle pair
   */
  auto spinParticleB() const { return this->IB(); }

  /**
   *  @brief Return the parity of the first particle in each particle pair
   */
  auto PA() const { return ParticlePairs::column( 10 ); }

  /**
   *  @brief Return the parity of the first particle in each particle pair
   */
  auto parityParticleA() const { return this->PA(); }

  /**
   *  @brief Return the parity of the second particle in each particle pair
   */
  auto PB() const { return ParticlePairs::column( 11 ); }

  /**
   *  @brief Return the parity of the second particle in each particle pair
   */
  auto parityParticleB() const { return this->PB(); }

  /**
   *  @brief Return the Q value for each particle pair
   */
  auto Q() const { return ParticlePairs::column( 6 ); }

  /**
   *  @brief Return the penetrability flag for each particle pair
   */
  auto PNT() const {

    using namespace njoy::tools;
    return ParticlePairs::column( 7 )
             | std20::views::transform( [] ( auto&& pnt )
                                           { return int( pnt ); } ); }

  /**
   *  @brief Return the penetrability flag for each particle pair
   */
  auto penetrabilityFlag() const { return this->PNT(); }

  /**
   *  @brief Return the shift factor flag for each particle pair
   */
  auto SHF() const {

    using namespace njoy::tools;
    return ParticlePairs::column( 8 )
             | std20::views::transform( [] ( auto&& shf )
                                           { return int( shf ); } ); }

  /**
   *  @brief Return the shift factor flag for each particle pair
   */
  auto shiftFactorFlag() const { return this->SHF(); }

  /**
   *  @brief Return the MT value associated to each particle pair
   */
  auto MT() const {

    using namespace njoy::tools;
    return ParticlePairs::column( 9 )
             | std20::views::transform( [] ( auto&& mt )
                                           { return int( mt ); } ); }

  using ListRecord::NC;
  using ListRecord::print;
};
