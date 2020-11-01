//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
UnresolvedBaseWithoutSpin() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] lvalues   the l values and the resonance parameters
 */
UnresolvedBaseWithoutSpin(
  std::vector< LValue >&& lvalues ) :
    // no need for a try ... catch: handled in derived class
    lvalues_( std::move( lvalues ) ) {

      verifySize( this->NLS() );
    }
