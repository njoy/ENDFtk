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
