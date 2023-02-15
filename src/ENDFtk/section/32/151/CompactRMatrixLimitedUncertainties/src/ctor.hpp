//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
CompactRMatrixLimitedUncertainties() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] pairs    the particle pairs
 *  @param[in] groups   the spin groups
 */
CompactRMatrixLimitedUncertainties( ParticlePairs&& pairs,
                                    std::vector< SpinGroup >&& groups ) :
    // no need for a try ... catch: nothing can go wrong here
    particle_pairs_( std::move( pairs ) ),
    spin_groups_( std::move( groups ) ) {

      verifySize( this->NJSX() );
    }

private:
/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
CompactRMatrixLimitedUncertainties(
    ParticlePairs&& pairs,
    Iterator& it, const Iterator& end, long& lineNumber,
    int MAT, int MF, int MT ) :
  CompactRMatrixLimitedUncertainties(
    std::move( pairs ),
    readSequence< SpinGroup >( it, end, lineNumber, MAT, MF, MT, pairs.NJSX() ) ) {}

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
CompactRMatrixLimitedUncertainties(
    Iterator& it, const Iterator& end, long& lineNumber,
    int MAT, int MF, int MT )
  try : CompactRMatrixLimitedUncertainties(
            ParticlePairs( it, end, lineNumber, MAT, MF, MT ),
            it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing R matrix limited "
               "resonance parameter uncertainties" );
    throw;
  }
