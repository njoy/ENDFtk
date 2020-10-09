//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
InterpolationSequenceRecord() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] interpolation   the interpolation record associated to the data
 *  @param[in] sequence        the data
 */
InterpolationSequenceRecord ( InterpolationRecord&& interpolation,
                              std::vector< Component >&& sequence ) :
  interpolation_( interpolation ),
  sequence_( sequence ) {

  verifyNZ( this->tab2().NZ(), sequence.size() );
  validateSequence( sequence );
}
