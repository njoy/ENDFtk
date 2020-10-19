//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
DefinedElsewhere() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] law    the law number to be used (-4, -5, -14, -15 only)
 */
DefinedElsewhere ( int LAW ) : law_( LAW ) {

  checkLAW( this->LAW() );
}
