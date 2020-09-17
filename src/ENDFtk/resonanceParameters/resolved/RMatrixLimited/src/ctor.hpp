/**
 *  @brief Constructor
 *
 *  @param[in] ifg      flag to indicate whether or not the widths are reduced
 *  @param[in] krl      the non relativistic kinematics flag
 *  @param[in] krm      the resonance formalism to be used
 *  @param[in] pairs    the particle pairs
 *  @param[in] groups   the spin groups
 */
RMatrixLimited( bool ifg, bool krl, int krm,
                ParticlePairs&& pairs,
                std::vector< SpinGroup >&& groups ) :
    // no need for a try ... catch: nothing can go wrong here
    ifg_( ifg ), krl_( krl ), krm_( krm ),
    particle_pairs_( std::move( pairs ) ),
    spin_groups_( std::move( groups ) ) {

      verifySize( this->NJS() );
    }

private:
/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
RMatrixLimited( bool ifg, bool krl, int krm,
                ParticlePairs&& pairs,
                int njs,
                Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT ) :
  RMatrixLimited( ifg, krl, krm,
                  std::move( pairs ),
                  readSequence< SpinGroup >( it, end, lineNumber,
                                             MAT, MF, MT, njs ) ) {}

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
RMatrixLimited( bool ifg, bool krl, int krm, int njs,
                Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT ) :
  RMatrixLimited( ifg, krl, krm,
                  ParticlePairs( it, end, lineNumber, MAT, MF, MT ), njs,
                  it, end, lineNumber, MAT, MF, MT ) {}

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
RMatrixLimited( ControlRecord&& cont,
                Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT ) :
  RMatrixLimited( cont.L1(), cont.N2(), cont.L2(), cont.N1(),
                  it, end, lineNumber, MAT, MF, MT ) {}

public:
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
RMatrixLimited( Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT )
  try : RMatrixLimited( ControlRecord( it, end, lineNumber, MAT, MF, MT ),
                        it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing R matrix limited "
               "resonance parameters" );
    throw;
  }
