InterpolationSequenceRecord ( InterpolationRecord&& interpolation,
                              std::vector< Component >&& sequence ) :
  interpolation_( interpolation ),
  sequence_( sequence ) {

  verifyNZ( this->tab2().NZ(), sequence.size() );
  validateSequence( sequence );
}

/*private:

template< typename Iterator >
InterpolationSequenceRecord ( InterpolationRecord&& interpolation,
                              Iterator& begin,
                              const Iterator& end,
                              long& lineNumber,
                              int MAT,
                              int MF,
                              int MT ) :
  InterpolationSequenceRecord(
    std::move( interpolation ),
    std::vector< Component >( readSequence( begin, end, lineNumber,
                                            MAT, MF, MT,
                                            interpolation.NZ() ) ) ) {}

public:

template< typename Iterator >
InterpolationSequenceRecord ( Iterator& begin,
                              const Iterator& end,
                              long& lineNumber,
                              int MAT,
                              int MF,
                              int MT ) :
  InterpolationSequenceRecord(
    InterpolationRecord( begin, end, lineNumber, MAT, MF, MT  ),
    begin, end, lineNumber, MAT, MF, MT ) {}
*/
