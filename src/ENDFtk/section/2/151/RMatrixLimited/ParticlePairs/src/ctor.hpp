private:
/**
 *  @brief Private intermediate constructor
 */
ParticlePairs( ListRecord&& list ) : ListRecord( std::move( list ) ) {

  verifySize( this->NPL(), this->L1() );
}

public:
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
 *  @param[in] ma    the mass of the first particle in each particle pair
 *  @param[in] mb    the mass of the first particle in each particle pair
 *  @param[in] za    the charge of the first particle in each particle pair
 *  @param[in] zb    the charge of the first particle in each particle pair
 *  @param[in] ia    the spin of the first particle in each particle pair
 *  @param[in] ib    the spin of the first particle in each particle pair
 *  @param[in] pa    the parity of the first particle in each particle pair
 *  @param[in] pb    the parity of the first particle in each particle pair
 *  @param[in] q     the mass of the first particle in each particle pair
 *  @param[in] pnt   the mass of the first particle in each particle pair
 *  @param[in] shf   the charge of the first particle in each particle pair
 *  @param[in] mt    the charge of the first particle in each particle pair
 */
ParticlePairs( std::vector< double >&& ma, std::vector< double >&& mb,
               std::vector< double >&& za, std::vector< double >&& zb,
               std::vector< double >&& ia, std::vector< double >&& ib,
               std::vector< double >&& pa, std::vector< double >&& pb,
               std::vector< double >&& q, std::vector< int >&& pnt,
               std::vector< int >&& shf, std::vector< int >&& mt )
  try : ParticlePairs(
          ListRecord( 0., 0., ma.size(), 0, 2 * ma.size(),
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
